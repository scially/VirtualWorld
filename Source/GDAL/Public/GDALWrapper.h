#pragma once

#include "ogrsf_frmts.h"
#include <stdexcept>

#include "CoreMinimal.h"


    namespace internal {
        class GDALDriverWrapper {
        public:
            GDALDriverWrapper() {
                GDALAllRegister();
            }
        };
    }

    class GDALWrapperException: public std::runtime_error
    {
    public:
        GDALWrapperException(const FString &_Message) : std::runtime_error(TCHAR_TO_UTF8(*_Message)){}
    };
    
    class OGRFeatureWrapper;
    class OGRLayerWrapper;
    class GDALDatasetWrapper;


   class OGRFeatureWrapper {
   public:
       friend class OGRLayerWrapper;

       OGRGeometry* GetGeometryRef() {
           return feature->GetGeometryRef();
       }

       double GetFieldAsDouble(GIntBig fid){
           return feature->GetFieldAsDouble(fid);
       }

       bool isValid() const{
           return feature != nullptr;
       }

       GIntBig GetFID(){
           return feature->GetFID();
       }

       int GetFieldCount() const
       {
            return feature->GetFieldCount();          
       }

       const char* GetFieldAsString(int i) const
       {
           return feature->GetFieldAsString(i);
       }

       const OGRFieldDefn* GetFieldDefnRef(int i) const
       {
           return feature->GetFieldDefnRef(i);
       }

   private:
       struct OGRFeatureDeleteWrapper{
           void operator() (OGRFeature *f){
               if(f != nullptr)
                   OGRFeature::DestroyFeature(f);
               f = nullptr;
           }
       };
       
       explicit OGRFeatureWrapper(OGRFeature *f){
           feature = TSharedPtr<OGRFeature>(f, OGRFeatureDeleteWrapper());
       }

       TSharedPtr<OGRFeature> feature;
   };


   class OGRLayerWrapper {
   public:
       friend class GDALDatasetWrapper;

       OGRFeatureWrapper GetNextFeature(){
           OGRFeature* feature = layer->GetNextFeature();
           return OGRFeatureWrapper(feature);
       }

       OGREnvelope GetExtent(int bForce = 1) {
           OGREnvelope envelope;
           OGRErr err = layer->GetExtent(&envelope, bForce);
           if (err != OGRERR_NONE)
               throw GDALWrapperException(TEXT("GetExtent error"));

           return envelope;
       }

       OGRFeatureWrapper GetFeature(GIntBig fid){
           OGRFeature* feature = layer->GetFeature(fid);
           if(feature == nullptr){
               throw GDALWrapperException(FString::Printf(TEXT("No feature %lld, %hs"), fid , "in Layer"));
           }
           return OGRFeatureWrapper(feature);
       }

       bool isValid() const {
           return true;
       }

       void ResetReading(){
           layer->ResetReading();
       }

       OGRSpatialReference* GetSpatialRef() {
           return layer->GetSpatialRef();
       }

       OGRFeatureDefn* GetLayerDefn(){
           return layer->GetLayerDefn();
       }

   private:
       explicit OGRLayerWrapper(OGRLayer *layer): layer(layer){}
       OGRLayer* layer;  // will auto dispose when ds close.
   };

   class GDALDatasetWrapper {
   public:
        friend class OGRLayerWrapper;
        static inline GDALDatasetWrapper open(const FString &pszFilename,
                                             unsigned int nOpenFlags = GDAL_OF_ALL,
                                             const char* const* papszAllowedDrivers = nullptr,
                                             const char* const* papszOpenOptions = nullptr,
                                             const char* const* papszSiblingFiles = nullptr){
           static internal::GDALDriverWrapper init;
           GDALDataset *dataset = (GDALDataset*)GDALOpenEx(TCHAR_TO_UTF8(*pszFilename),
                                                           nOpenFlags,
                                                           papszAllowedDrivers,
                                                           papszOpenOptions,
                                                           papszSiblingFiles);
           if (dataset == nullptr)
               throw GDALWrapperException(TEXT("Can't open dataset ") + pszFilename);

           return GDALDatasetWrapper(dataset);
       }

       OGRLayerWrapper GetLayer(int iLayer){
            OGRLayer* layer = ds->GetLayer(iLayer);
            return OGRLayerWrapper(layer);
       }

       OGRLayerWrapper GetLayerByName(const FString &nLayer){
            OGRLayer* layer = ds->GetLayerByName(TCHAR_TO_UTF8(*nLayer));
            return OGRLayerWrapper(layer);
       }
       bool isValid() const{
           return true;
       }

   private:
       struct GDALDatasetDeleteWrapper{
           void operator() (GDALDataset *dataset){
               if(dataset != nullptr)
                   GDALClose(dataset);
           }
       };
       // dataset 将被 GDALDatasetWrapper 接管
       explicit GDALDatasetWrapper(GDALDataset *dataset){
           ds = TSharedPtr<GDALDataset>(dataset, GDALDatasetDeleteWrapper());
       }
       TSharedPtr<GDALDataset> ds;
   };

