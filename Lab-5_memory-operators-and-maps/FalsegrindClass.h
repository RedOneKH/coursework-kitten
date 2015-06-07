/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the class definition of Falsegrind, the complete
dynamic memory manager for this lab. The name "Falsegrind" was chosen as a
play on the name "Valgrind," which is a legitimate, well-known programming
tool for memory debugging, leak detection, and profiling.
*/

#ifndef FALSEGRIND_CLASS_H
#define FALSEGRIND_CLASS_H

#include "DynamicMemoryCounter.h"
#include "DynamicMemoryMap.h"
#include <memory>

class FalsegrindClass
{
private:
	static bool modifyLock;

	static FalsegrindClass * fgInstance;

	inline std::pair<bool, size_t> * tryAccess(void *address);
protected:
	DynamicMemoryCounter *dm_count;
	DynamicMemoryMap *dm_map;

	// protected constructor because this is a singleton class
	FalsegrindClass();
	// protected destructor forces user to call resetInstance(),
	// the proper way of deleting this class
	~FalsegrindClass()                                            { DynamicMemoryCounter::resetInstance(); DynamicMemoryMap::resetInstance(); }
public:
	// get/reset instance and check if instance exists methods
	static FalsegrindClass * instance();
	static void resetInstance()                                   { modifyLock = true; delete fgInstance; fgInstance = 0; modifyLock = false; }
	static bool exists()                                          { return (fgInstance != 0); }
	bool componentsExist()                                        { return (DynamicMemoryMap::exists() && DynamicMemoryCounter::exists()); }

	// getters/setters
	bool isLockedForModification() const                          { return modifyLock; }
	/* Note that there is no setter for the modifyLock because this variable can only be changed
	inside this class. Changing the lock from outside (i.e. in the dynamic memory overload
	operators) could easily cause bugs.*/

	// DynamicMemoryCounter methods
	virtual long getAllocationCount() const                       { return dm_count->getAllocationCount(); }
	virtual void incrementAllocationCount()                       { dm_count->incrementAllocationCount(); }
	virtual void decrementAllocationCount()                       { dm_count->decrementAllocationCount(); }

	// DynamicMemoryMap methods
	virtual const size_t & getByteSize(void *address);
	virtual void addMemoryMapping(void *address, size_t byteSize);
	virtual void markMappingForDelete(void *address);
	virtual void deleteMemoryMapping(void *address);
};

// initialize static members
bool FalsegrindClass::modifyLock = false;

// initialize static member instance later in instance()
FalsegrindClass * FalsegrindClass::fgInstance = 0;

inline std::pair<bool, size_t> * FalsegrindClass::tryAccess(void *address)
{
	std::pair<bool, size_t> *value;

	try
	{
		value = &(dm_map->at(address));
	}
	catch (const std::out_of_range &exception)
	{
		value = 0;
	}

	return value;
}

FalsegrindClass::FalsegrindClass()
{
	dm_count = DynamicMemoryCounter::instance();
	dm_map = DynamicMemoryMap::instance();
}

FalsegrindClass * FalsegrindClass::instance()
{
	if (!fgInstance)
	{
		fgInstance = new FalsegrindClass();
	}

	return fgInstance;
}

const size_t & FalsegrindClass::getByteSize(void *address)
{
	// get map node if it exists, otherwise assign 0
	std::pair<bool, size_t> *value = this->tryAccess(address);

	// if the value exists and is active, return the size_t
	// else return 0
	return (value && value->first ? value->second : 0);
}

void FalsegrindClass::addMemoryMapping(void *address, size_t byteSize)
{
	modifyLock = true;

	(*dm_map)[address] = std::pair<bool, size_t>(true, byteSize);

	modifyLock = false;
}

void FalsegrindClass::markMappingForDelete(void *address)
{
	// get map node if it exists, otherwise assign 0
	std::pair<bool, size_t> *value = this->tryAccess(address);

	modifyLock = true;

	if (value) // if value exists, mark the node as inactive
	{
		value->first = false; 
	}

	modifyLock = false;
}

void FalsegrindClass::deleteMemoryMapping(void *address)
{
	modifyLock = true;

	// if key exists, delete from the map
	if (dm_map->find(address) != dm_map->end())
	{
		dm_map->erase(address);
	}

	modifyLock = false;
}

#endif // FALSEGRIND_CLASS_H