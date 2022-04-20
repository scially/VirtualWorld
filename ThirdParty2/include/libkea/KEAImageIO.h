/*
 *  KEAImageIO.h
 *  LibKEA
 *
 *  Created by Pete Bunting on 02/07/2012.
 *  Copyright 2012 LibKEA. All rights reserved.
 *
 *  This file is part of LibKEA.
 *
 *  Permission is hereby granted, free of charge, to any person 
 *  obtaining a copy of this software and associated documentation 
 *  files (the "Software"), to deal in the Software without restriction, 
 *  including without limitation the rights to use, copy, modify, 
 *  merge, publish, distribute, sublicense, and/or sell copies of the 
 *  Software, and to permit persons to whom the Software is furnished 
 *  to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be 
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR 
 *  ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
 *  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef KEAImageIO_H
#define KEAImageIO_H

#include <iostream>
#include <string>
#include <vector>

#include "H5Cpp.h"

#include "libkea/KEACommon.h"
#include "libkea/KEAException.h"
#include "libkea/KEAAttributeTable.h"
#include "libkea/KEAAttributeTableInMem.h"
#include "libkea/KEAAttributeTableFile.h"

namespace kealib{
        
    class KEA_EXPORT KEAImageIO
    {
    public:
        KEAImageIO();
                
        void openKEAImageHeader(H5::H5File *keaImgH5File);
        
        void writeImageBlock2Band(uint32_t band, void *data, uint64_t xPxlOff, uint64_t yPxlOff, uint64_t xSizeOut, uint64_t ySizeOut, uint64_t xSizeBuf, uint64_t ySizeBuf, KEADataType inDataType);
        void readImageBlock2Band(uint32_t band, void *data, uint64_t xPxlOff, uint64_t yPxlOff, uint64_t xSizeIn, uint64_t ySizeIn, uint64_t xSizeBuf, uint64_t ySizeBuf, KEADataType inDataType);
        
        void createMask(uint32_t band, uint32_t deflate=KEA_DEFLATE);
        void writeImageBlock2BandMask(uint32_t band, void *data, uint64_t xPxlOff, uint64_t yPxlOff, uint64_t xSizeOut, uint64_t ySizeOut, uint64_t xSizeBuf, uint64_t ySizeBuf, KEADataType inDataType);
        void readImageBlock2BandMask(uint32_t band, void *data, uint64_t xPxlOff, uint64_t yPxlOff, uint64_t xSizeIn, uint64_t ySizeIn, uint64_t xSizeBuf, uint64_t ySizeBuf, KEADataType inDataType);
        bool maskCreated(uint32_t band);
        
        void setImageMetaData(std::string name, std::string value);
        std::string getImageMetaData(std::string name);
        std::vector<std::string> getImageMetaDataNames();
        std::vector< std::pair<std::string, std::string> > getImageMetaData();
        void setImageMetaData(std::vector< std::pair<std::string, std::string> > data);
        
        void setImageBandMetaData(uint32_t band, std::string name, std::string value);
        std::string getImageBandMetaData(uint32_t band, std::string name);
        std::vector<std::string> getImageBandMetaDataNames(uint32_t band);
        std::vector< std::pair<std::string, std::string> > getImageBandMetaData(uint32_t band);
        void setImageBandMetaData(uint32_t band, std::vector< std::pair<std::string, std::string> > data);
        
        void setImageBandDescription(uint32_t band, std::string description);
        std::string getImageBandDescription(uint32_t band);
        
        void setNoDataValue(uint32_t band, const void *data, KEADataType inDataType);
        void getNoDataValue(uint32_t band, void *data, KEADataType inDataType);
        void undefineNoDataValue(uint32_t band);
        
        
        std::vector<KEAImageGCP*>* getGCPs();
        void setGCPs(std::vector<KEAImageGCP*> *gcps, std::string projWKT);
        uint32_t getGCPCount();
        std::string getGCPProjection();
        void setGCPProjection(std::string projWKT);
        
        void setSpatialInfo(KEAImageSpatialInfo *spatialInfo);
        KEAImageSpatialInfo* getSpatialInfo();
                
        uint32_t getNumOfImageBands();
        
        uint32_t getImageBlockSize(uint32_t band);
        
        KEADataType getImageBandDataType(uint32_t band);
        
        std::string getKEAImageVersion();
        
        void setImageBandLayerType(uint32_t band, KEALayerType imgLayerType);
        KEALayerType getImageBandLayerType(uint32_t band);
        
        void setImageBandClrInterp(uint32_t band, KEABandClrInterp imgLayerClrInterp);
        KEABandClrInterp getImageBandClrInterp(uint32_t band);
        
        void createOverview(uint32_t band, uint32_t overview, uint64_t xSize, uint64_t ySize);
        void removeOverview(uint32_t band, uint32_t overview);
        uint32_t getOverviewBlockSize(uint32_t band, uint32_t overview);
        void writeToOverview(uint32_t band, uint32_t overview, void *data, uint64_t xPxlOff, uint64_t yPxlOff, uint64_t xSizeOut, uint64_t ySizeOut, uint64_t xSizeBuf, uint64_t ySizeBuf, KEADataType inDataType);
        void readFromOverview(uint32_t band, uint32_t overview, void *data, uint64_t xPxlOff, uint64_t yPxlOff, uint64_t xSizeIn, uint64_t ySizeIn, uint64_t xSizeBuf, uint64_t ySizeBuf, KEADataType inDataType);
        uint32_t getNumOfOverviews(uint32_t band);
        void getOverviewSize(uint32_t band, uint32_t overview, uint64_t *xSize, uint64_t *ySize);
                
        KEAAttributeTable* getAttributeTable(KEAATTType type, uint32_t band);
        void setAttributeTable(KEAAttributeTable* att, uint32_t band, uint32_t chunkSize=KEA_ATT_CHUNK_SIZE, uint32_t deflate=KEA_DEFLATE);
        bool attributeTablePresent(uint32_t band);
        uint32_t getAttributeTableChunkSize(uint32_t band);
        
        void close();

        /**
         * Adds a new image band to the file.
         */
        virtual void addImageBand(const KEADataType dataType, const std::string bandDescrip, const uint32_t imageBlockSize = KEA_IMAGE_CHUNK_SIZE, const uint32_t attBlockSize = KEA_ATT_CHUNK_SIZE, const uint32_t deflate = KEA_DEFLATE);

        static H5::H5File* createKEAImage(std::string fileName, KEADataType dataType, uint32_t xSize, uint32_t ySize, uint32_t numImgBands, std::vector<std::string> *bandDescrips=NULL, KEAImageSpatialInfo *spatialInfo=NULL, uint32_t imageBlockSize=KEA_IMAGE_CHUNK_SIZE, uint32_t attBlockSize=KEA_ATT_CHUNK_SIZE, int mdcElmts=KEA_MDC_NELMTS, hsize_t rdccNElmts=KEA_RDCC_NELMTS, hsize_t rdccNBytes=KEA_RDCC_NBYTES, double rdccW0=KEA_RDCC_W0, hsize_t sieveBuf=KEA_SIEVE_BUF, hsize_t metaBlockSize=KEA_META_BLOCKSIZE, uint32_t deflate=KEA_DEFLATE);
        static bool isKEAImage(std::string fileName);
        static H5::H5File* openKeaH5RW(std::string fileName, int mdcElmts=KEA_MDC_NELMTS, hsize_t rdccNElmts=KEA_RDCC_NELMTS, hsize_t rdccNBytes=KEA_RDCC_NBYTES, double rdccW0=KEA_RDCC_W0, hsize_t sieveBuf=KEA_SIEVE_BUF, hsize_t metaBlockSize=KEA_META_BLOCKSIZE);
        static H5::H5File* openKeaH5RDOnly(std::string fileName, int mdcElmts=KEA_MDC_NELMTS, hsize_t rdccNElmts=KEA_RDCC_NELMTS, hsize_t rdccNBytes=KEA_RDCC_NBYTES, double rdccW0=KEA_RDCC_W0, hsize_t sieveBuf=KEA_SIEVE_BUF, hsize_t metaBlockSize=KEA_META_BLOCKSIZE);
        virtual ~KEAImageIO();

    protected:
        /********** STATIC PROTECTED **********/
        /**
         * Converts KEA datatypes to the respective standard HDF5 datatypes.
         */
        static H5::DataType convertDatatypeKeaToH5STD(const KEADataType dataType);

        /**
         * Converts KEA datatypes to the respective native HDF5 datatypes.
         */
        static H5::DataType convertDatatypeKeaToH5Native( const KEADataType dataType);

        /**
         * Adds an image band to the specified file. Does NOT flush the file
         * buffer.
         *
         * NOTE: attBlockSize doesn't have any effect at the moment
         */
        static void addImageBandToFile(H5::H5File *keaImgH5File, const KEADataType dataType, const uint32_t xSize, const uint32_t ySize, const uint32_t bandIndex, std::string bandDescrip, const uint32_t imageBlockSize, const uint32_t attBlockSize, const uint32_t deflate);

        /**
         * Updates the number of image bands in the file metadata. Does NOT
         * flush the file buffer.
         */
        static void setNumImgBandsInFileMetadata(H5::H5File *keaImgH5File, const uint32_t numImgBands);

        static H5::CompType* createGCPCompTypeDisk();
        static H5::CompType* createGCPCompTypeMem();
        
        static std::string readString(H5::DataSet& dataset, H5::DataType strDataType);
        
        /********** PROTECTED MEMBERS **********/
        bool fileOpen;
        H5::H5File *keaImgFile;
        KEAImageSpatialInfo *spatialInfoFile;
        uint32_t numImgBands;
        std::string keaVersion;
    };
    
}

// returns the current KEA version as a double
extern "C" KEA_EXPORT double get_kealibversion();

#endif




