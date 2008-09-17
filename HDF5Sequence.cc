
#include "config_hdf5.h"

#include <string>
#include <ctype.h>

#include "HDF5Sequence.h"
#include "InternalErr.h"

BaseType *HDF5Sequence::ptr_duplicate()
{
    return new HDF5Sequence(*this);
}


HDF5Sequence::HDF5Sequence(const string & n, const string &d) : Sequence(n, d)
{
    ty_id = -1;
    dset_id = -1;
}

HDF5Sequence::~HDF5Sequence()
{
}

bool HDF5Sequence::read()
{
    throw InternalErr(__FILE__, __LINE__,
                      "HDF5Sequence::read(): Unimplemented method.");

    return false;
}

void HDF5Sequence::set_did(hid_t dset)
{
    dset_id = dset;
}

void HDF5Sequence::set_tid(hid_t type)
{
    ty_id = type;
}

hid_t HDF5Sequence::get_did()
{
    return dset_id;
}

hid_t HDF5Sequence::get_tid()
{
    return ty_id;
}
