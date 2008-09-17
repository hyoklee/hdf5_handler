#include "config_hdf5.h"
#include "debug.h"
#include <string>
#include <ctype.h>

#include "InternalErr.h"

#include "h5dds.h"
#include "HDF5UInt16.h"
#include "HDF5Structure.h"

typedef struct s2_t {
    /// Buffer for a 16 bit integer in compound data
    dods_int16 a;
} s2_t;


HDF5UInt16::HDF5UInt16(const string & n, const string &d) : UInt16(n, d)
{
    ty_id = -1;
    dset_id = -1;

}

BaseType *HDF5UInt16::ptr_duplicate()
{

    return new HDF5UInt16(*this);
}

bool HDF5UInt16::read()
{
    if (read_p())
        return false;

    if (return_type(ty_id) == "UInt16") {
        dods_uint16 buf;
	get_data(dset_id, (void *) &buf);
        set_read_p(true);
	set_value(buf);
    }
    
    if (return_type(ty_id) == "Structure") {

        BaseType *q = get_parent();
        if (!q)
        	throw InternalErr(__FILE__, __LINE__, "null pointer");
        HDF5Structure &p = dynamic_cast < HDF5Structure & >(*q);

        char Msgi[256];
#ifdef DODS_DEBUG
        int i = H5Tget_nmembers(ty_id);
#endif
        int j = 0;
        int k = 0;

        hid_t s1_tid = H5Tcreate(H5T_COMPOUND, sizeof(s2_t));
        hid_t stemp_tid;

        s2_t *buf = 0;
	try {
	    buf = new s2_t[p.get_entire_array_size()];
        string myname = name();
        string parent_name;


        DBG(cerr
            << "=read() ty_id=" << ty_id
            << " name=" << myname << " no of members =" << i << endl);
        while (q != NULL) {

            if (q->is_constructor_type()) {     // Grid, structure or sequence
                if (k == 0) {
                    // Bottom level structure
                    DBG(cerr << "=read() my_name " << myname.
                        c_str() << endl);
                    H5Tinsert(s1_tid, myname.c_str(), HOFFSET(s2_t, a),
                              H5T_NATIVE_UINT16);
                } else {
                    DBG(cerr << k << "=read() parent_name=" << parent_name
                        << endl);

                    stemp_tid = H5Tcreate(H5T_COMPOUND, sizeof(s2_t));
                    H5Tinsert(stemp_tid, parent_name.c_str(), 0, s1_tid);
                    s1_tid = stemp_tid;

                }
                // Remember the last parent name.
                parent_name = q->name();
                p = dynamic_cast < HDF5Structure & >(*q);
                // Remember the index of array from the last parent.
                j = p.get_array_index();
                q = q->get_parent();

            } else {
                q = NULL;
            }
            k++;
        }                       // while ()


        if (H5Dread(dset_id, s1_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf) <
            0) {
            throw InternalErr(__FILE__, __LINE__,
                              string
                              ("hdf5_dods server failed when getting int32 data for structure\n")
                              + Msgi);
        }

        set_read_p(true);
        DBG(cerr << "index " << j << endl);
#if 0
        dods_int16 intg16 = buf[j].a;
        val2buf(&intg16);
#endif
	set_value(buf[j].a);
	delete[] buf;
	}
	catch(...) {
	    delete[] buf;
	    throw;
	}

    }                           // In case of structure


    return false;
}

void HDF5UInt16::set_did(hid_t dset)
{
    dset_id = dset;
}

void HDF5UInt16::set_tid(hid_t type)
{
    ty_id = type;
}

hid_t HDF5UInt16::get_did()
{
    return dset_id;
}

hid_t HDF5UInt16::get_tid()
{
    return ty_id;
}
