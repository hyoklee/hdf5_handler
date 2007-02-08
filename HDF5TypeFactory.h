
// -*- mode: c++; c-basic-offset:4 -*-

// This file is part of ff_handler a FreeForm API handler for the OPeNDAP
// DAP2 data server.

// Copyright (c) 2005 OPeNDAP, Inc.
// Author: James Gallagher <jgallagher@opendap.org>
//
// This is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
// 
// This software is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.

#ifndef hdf5_type_factory_h
#define hdf5_type_factory_h

#include <string>

// Class declarations; Make sure to include the corresponding headers in the
// implementation file.

class HDF5Byte;
class HDF5Int16;
class HDF5UInt16;
class HDF5Int32;
class HDF5UInt32;
class HDF5Float32;
class HDF5Float64;
class HDF5Str;
class HDF5Url;
class HDF5Array;
class HDF5Structure;
class HDF5Sequence;
class HDF5Grid;

/** A factory for the HDF5 Data Handler types.

    @author James Gallagher
    @see DDS */
class HDF5TypeFactory: public BaseTypeFactory {
public:
    HDF5TypeFactory() {} 
    virtual ~HDF5TypeFactory() {}

    virtual Byte *NewByte(const string &n = "") const;
    virtual Int16 *NewInt16(const string &n = "") const;
    virtual UInt16 *NewUInt16(const string &n = "") const;
    virtual Int32 *NewInt32(const string &n = "") const;
    virtual UInt32 *NewUInt32(const string &n = "") const;
    virtual Float32 *NewFloat32(const string &n = "") const;
    virtual Float64 *NewFloat64(const string &n = "") const;

    virtual Str *NewStr(const string &n = "") const;
    virtual Url *NewUrl(const string &n = "") const;

    virtual Array *NewArray(const string &n = "", BaseType *v = 0) const;
    virtual Structure *NewStructure(const string &n = "") const;
    virtual Sequence *NewSequence(const string &n = "") const;
    virtual Grid *NewGrid(const string &n = "") const;
};

#endif // hdf5_type_factory_h