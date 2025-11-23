// learn_itk_win.cpp: Defines the entry point for the application.
//

#include "learn_itk_win.h"

using namespace std;

int main()
{
	cout << "=== Learn ITK Win Project ===" << endl;
	cout << "ITK Version: " << ITK_VERSION_MAJOR << "." << ITK_VERSION_MINOR << "." << ITK_VERSION_PATCH << endl;
	cout << endl;
	
	// Basic ITK Example: Create a simple image
	using PixelType = unsigned char;
	using ImageType = itk::Image<PixelType, 2>;
	
	// Create an image
	ImageType::Pointer image = ImageType::New();
	
	// Set the image region
	ImageType::IndexType start;
	start[0] = 0;
	start[1] = 0;
	
	ImageType::SizeType size;
	size[0] = 200;
	size[1] = 300;
	
	ImageType::RegionType region;
	region.SetSize(size);
	region.SetIndex(start);
	
	image->SetRegions(region);
	image->Allocate();
	image->FillBuffer(0);  // Initialize to 0
	
	cout << "1. Created a " << size[0] << "x" << size[1] << " ITK image" << endl;
	
	// Fill image data using an iterator (more efficient)
	using IteratorType = itk::ImageRegionIterator<ImageType>;
	IteratorType iterator(image, image->GetRequestedRegion());
	
	ImageType::IndexType pixelIndex;
	for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
	{
		pixelIndex = iterator.GetIndex();
		// Create a simple gradient pattern
		PixelType value = static_cast<PixelType>((pixelIndex[0] + pixelIndex[1]) % 256);
		iterator.Set(value);
	}
	
	cout << "2. Finished filling image data using an iterator" << endl;
	
	// Get image information
	cout << "3. Image Information:" << endl;
	cout << "   - Image Region: " << image->GetLargestPossibleRegion() << endl;
	cout << "   - Image Size: " << image->GetLargestPossibleRegion().GetSize() << endl;
	cout << "   - Pixel Spacing: " << image->GetSpacing() << endl;
	cout << "   - Image Origin: " << image->GetOrigin() << endl;
	
	// Calculate image statistics
	PixelType minValue = 255, maxValue = 0;
	double sum = 0;
	unsigned long pixelCount = 0;
	
	for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
	{
		PixelType value = iterator.Get();
		if (value < minValue) minValue = value;
		if (value > maxValue) maxValue = value;
		sum += value;
		pixelCount++;
	}
	
	double meanValue = sum / pixelCount;
	
	cout << "4. Image Statistics:" << endl;
	cout << "   - Min Value: " << static_cast<int>(minValue) << endl;
	cout << "   - Max Value: " << static_cast<int>(maxValue) << endl;
	cout << "   - Mean Value: " << meanValue << endl;
	cout << "   - Total Pixels: " << pixelCount << endl;
	
	// Test image access
	ImageType::IndexType testIndex;
	testIndex[0] = 100;
	testIndex[1] = 150;
	PixelType testValue = image->GetPixel(testIndex);
	
	cout << "5. Pixel value at [100,150]: " << static_cast<int>(testValue) << endl;
	
	cout << endl;
	cout << "=== ITK Integration Test Successful! ===" << endl;
	
	return 0;
}
