/*
 *  KEAAttributeTableFile.h
 *  LibKEA
 *
 *  Created by Pete Bunting on 20/07/2012.
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

#ifndef KEAAttributeTableFile_H
#define KEAAttributeTableFile_H

#include <iostream>
#include <string>
#include <vector>

#include "H5Cpp.h"

#include "libkea/KEACommon.h"
#include "libkea/KEAException.h"
#include "libkea/KEAAttributeTable.h"

namespace kealib{
       
    class KEA_EXPORT KEAAttributeTableFile : public KEAAttributeTable
    {
    public:
        KEAAttributeTableFile(H5::H5File *keaImgIn, const std::string &bandPathBaseIn, size_t numRowsIn, size_t chunkSizeIn, unsigned int deflateIn=KEA_DEFLATE);
        
        bool getBoolField(size_t fid, const std::string &name) const;
        int64_t getIntField(size_t fid, const std::string &name) const;
        double getFloatField(size_t fid, const std::string &name) const;
        std::string getStringField(size_t fid, const std::string &name) const;

        void setBoolField(size_t fid, const std::string &name, bool value);
        void setIntField(size_t fid, const std::string &name, int64_t value);
        void setFloatField(size_t fid, const std::string &name, double value);
        void setStringField(size_t fid, const std::string &name, const std::string &value);
        
        bool getBoolField(size_t fid, size_t colIdx) const;
        int64_t getIntField(size_t fid, size_t colIdx) const;
        double getFloatField(size_t fid, size_t colIdx) const;
        std::string getStringField(size_t fid, size_t colIdx) const;

        void getBoolFields(size_t startfid, size_t len, size_t colIdx, bool *pbBuffer) const;
        void getIntFields(size_t startfid, size_t len, size_t colIdx, int64_t *pnBuffer) const;
        void getFloatFields(size_t startfid, size_t len, size_t colIdx, double *pfBuffer) const;
        void getStringFields(size_t startfid, size_t len, size_t colIdx, std::vector<std::string> *psBuffer) const;
        void getNeighbours(size_t startfid, size_t len, std::vector<std::vector<size_t>* > *neighbours) const;
        
        void setBoolField(size_t fid, size_t colIdx, bool value);
        void setIntField(size_t fid, size_t colIdx, int64_t value);
        void setFloatField(size_t fid, size_t colIdx, double value);
        void setStringField(size_t fid, size_t colIdx, std::string value);

        void setBoolFields(size_t startfid, size_t len, size_t colIdx, bool *pbBuffer);
        void setIntFields(size_t startfid, size_t len, size_t colIdx, int64_t *pnBuffer);
        void setFloatFields(size_t startfid, size_t len, size_t colIdx, double *pfBuffer);
        void setStringFields(size_t startfid, size_t len, size_t colIdx, std::vector<std::string> *papszStrList);
        void setNeighbours(size_t startfid, size_t len, std::vector<std::vector<size_t>* > *neighbours);

        KEAATTFeature* getFeature(size_t fid) const;
        
        size_t getSize() const;
        
        void addAttBoolField(KEAATTField field, bool val);
        void addAttIntField(KEAATTField field, int64_t val);
        void addAttFloatField(KEAATTField field, float val);
        void addAttStringField(KEAATTField field, const std::string &val);
        
        void addRows(size_t numRows);
        
        static KEAAttributeTable* createKeaAtt(H5::H5File *keaImg, unsigned int band, unsigned int chunkSize=KEA_ATT_CHUNK_SIZE, unsigned int deflate=KEA_DEFLATE);
        void exportToKeaFile(H5::H5File *keaImg, unsigned int band, unsigned int chunkSize=KEA_ATT_CHUNK_SIZE, unsigned int deflate=KEA_DEFLATE);
        
        ~KEAAttributeTableFile();
    protected:
        size_t numRows;
        size_t chunkSize;
        unsigned int deflate;
        H5::H5File *keaImg;
        std::string bandPathBase;

        void updateSizeHeader(hsize_t nbools, hsize_t nints, hsize_t nfloats, hsize_t nstrings);
};
    
}


#endif




