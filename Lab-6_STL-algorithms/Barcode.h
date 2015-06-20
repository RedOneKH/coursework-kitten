/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the Barcode class, which will be part of the
patient data.
*/

#ifndef BARCODE_H_
#define BARCODE_H_

#include <bitset>

class Barcode
{
private:
	typedef unsigned int uint;

	uint encryptedBarcode;
	std::bitset<15> binaryBarcode;
public:
	// constructors and destructor
	Barcode()
		: encryptedBarcode(0),
		binaryBarcode(0) {}

	Barcode(const Barcode &toCopy)
		: encryptedBarcode(toCopy.encryptedBarcode),
		binaryBarcode(toCopy.binaryBarcode) {}

	Barcode(uint ebar)
		: encryptedBarcode(ebar),
		binaryBarcode(encryptedBarcode) {}

	~Barcode() {}

	// getters/setters
	uint getEncryptedBarcode() const { return encryptedBarcode; }

	const std::bitset<15> & getBinaryBarcode() const { return binaryBarcode; }

	void setBarcode(uint ebar)
	{
		encryptedBarcode = ebar;
		binaryBarcode = std::bitset<15>(encryptedBarcode);
	}

	// operator overloads
	Barcode & operator=(const Barcode &toCopy)
	{
		encryptedBarcode = toCopy.encryptedBarcode;
		binaryBarcode = toCopy.binaryBarcode;
		return *this;
	}

	friend bool operator==(const Barcode &left, const Barcode &right)
	{
		return (left.encryptedBarcode == right.encryptedBarcode);
	}
};

#endif // BARCODE_H_