// This file is part of hdf5_handler a HDF5 file handler for the OPeNDAP
// data server.

// Author: Hyo-Kyung Lee <hyoklee@hdfgroup.org> and Muqun Yang
// <myang6@hdfgroup.org> 

// Copyright (c) 2009 The HDF Group, Inc. and OPeNDAP, Inc.
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
// You can contact The HDF Group, Inc. at 1901 South First Street,
// Suite C-2, Champaign, IL 61820  

#ifndef _hdf5eosarray_h
#define _hdf5eosarray_h 1

#include <H5Ipublic.h>

#include "Array.h"
#include "h5get.h"

using namespace libdap;

////////////////////////////////////////////////////////////////////////////////
/// A special class for handling array in NASA EOS HDF5 file.
///
/// This class converts NASA EOS HDF5 array type into DAP array.
/// 
/// @author Hyo-Kyung Lee   (hyoklee@hdfgroup.org)
/// @author Kent Yang       (ymuqun@hdfgroup.org)
/// @author James Gallagher (jgallagher@opendap.org)
///
/// Copyright (c) 2007 HDF Group
/// Copyright (c) 1999 National Center for Supercomputing Applications.
/// 
/// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
class HDF5ArrayEOS:public Array {

  private:
    int d_num_dim;
    int d_num_elm;
    hid_t d_dset_id;
    hid_t d_ty_id;
    size_t d_memneed;

    int format_constraint(int *cor, int *step, int *edg);
    dods_float32 *get_dimension_data(dods_float32 * buf, int start,
                                     int stride, int stop, int count);

  public:
    /// Constructor
    HDF5ArrayEOS(const string &n, const string &d, BaseType * v);
    virtual ~ HDF5ArrayEOS();

    /// Clone this instance.
    /// 
    /// Allocate a new instance and copy *this into it. This method must perform a deep copy.
    /// \return A newly allocated copy of this class
    virtual BaseType *ptr_duplicate();

    /// Reads HDF5 NASA EOS array data into local buffer
    virtual bool read();

    /// remembers memory size needed.
    void set_memneed(size_t need);

    /// remembers number of dimensions of this array.
    void set_numdim(int ndims);

    /// remembers number of elements in this array.  
    void set_numelm(int nelms);


    /// See return_type function defined in h5dds.cc.
    friend string return_type(hid_t datatype);
};

#endif
