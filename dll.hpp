#ifndef DLL_HPP_2434312941
#define DLL_HPP_2434312941


#if defined(_MSC_VER)
	// Visual Studio compiler.
    #if defined(SWEIDMT_DLL_EXPORTS)
        #define SWEIDMT_DLL_IMPORT_EXPORT __declspec(dllexport)
	#else
        #define SWEIDMT_DLL_IMPORT_EXPORT __declspec(dllimport)
	#endif
#else
	// Other compilers.
    #define SWEIDMT_DLL_IMPORT_EXPORT
#endif

#define IMAGE_WIDTH 512
#define IMAGE_SIZE (IMAGE_WIDTH*IMAGE_WIDTH)
#define HU_WINDOW_WIDTH 4096
#define HU_MIN -1024
#define HU_MAX (HU_WINDOW_WIDTH + HU_MIN - 1)
#define SHORT_MAX 32767 /*short int maximum*/

/// return error types collected in one enum
typedef enum _return_type	
{
	DLL_RETURN_OK = 0, ///< everything is ok, successful termination
	DLL_RETURN_ERROR_SIZE = -1, ///< the size parameter is incorrect
	DLL_RETURN_ERROR_WINDOWING = -2, ///< the windowing parameters are incorrect
	DLL_RETURN_ERROR_LAYER = -3, ///< the layer parameter is incorrect
	DLL_RETURN_ERROR_SEGMENTATION = -4, ///< the segmentation threshold is incorrect
	DLL_RETURN_ERROR_NULLPTR = -5, ///< a pointer type parameter is null
	DLL_RETURN_ERROR_SEED_POS = -6, ///< the seed voxel is outside of the image range
	DLL_RETURN_ERROR_SILENT = -99 ///< silent error, e.g. when functions are called upon startup with uninitialised values
} return_t;


typedef struct
{
	short *data;
	int width;
	int heigth;
	int numSlices;
	double pixelSpacingXY;
	double pixelSpacingZ;
} image3D;

typedef struct
{
	unsigned char *data;
	int width;
	int heigth;
} image2D;

typedef struct
{
	int x;
	int y;
	int z;
} voxel;

extern "C"
{
	/**
	 * \brief Calculates the windowed image slice.
	 *
	 * Calculates the windowed image slice based on the windowing parameters.
	 * \param image The whole data set of image slices.
	 * \param layer Current layer of the image data set to be processed. [0..image.numSlices]
	 * \param windowingStart Start value for windowing. [HU_MIN..HU_MAX]
	 * \param windowingWidth Width value for windowing. [1..HU_WINDOW_WIDTH]
	 * \param returnImage Already allocated array to return windowed image of the respective layer.
	 * \return 0 if ok. -1 if size parameter incorrect. -2 if windowing parameters incorrect. -3 if layer parameter incorrect. -5 if data pointer is null. Silent error -99 if size equals 0.
	 */
	SWEIDMT_DLL_IMPORT_EXPORT return_t windowing(const image3D &image, const int &layer, const short &windowingStart, const short &windowingWidth, image2D &returnImage);	

	/**
	 * \brief Calculates the intensity map / pseudo 3D image.
	 *
	 * Calculates the intensity map / pseudo 3D image. The computation is based on a thresholding of the volume image and a subsequent computation of the depth along one dimension.
	 * Note that the returned image is padded with a width of 1 pixel.
	 * \param image The whole data set of image slices.
	 * \param segmentationThresh The threshold for opaque voxels. [HU_MIN..HU_MAX]
	 * \param returnImage Already allocated array to return intensity map.
	 * \return 0 if ok. -1 if size parameter incorrect. -4 if segmentation threshold is incorrect. -5 if data pointer is null. Silent error -99 if size equals 0.
	 */
	SWEIDMT_DLL_IMPORT_EXPORT return_t intensityMap(const image3D &image, const short &segmentationThresh, image2D &returnImage);

	/**
	 * \brief Performs region growing algorithm.
	 *
	 * Thresholds the whole image and computes a connected region starting from a seed point. Returns a volume where every voxel belonging to the region is set to 1.
	 * \param image The whole data set of image slices.
	 * \param seed The starting position of the region growing. Neighbouring voxels fullfilling the threshold-criterion will be added recursively until the region is fully grown. 
	 * \param segmentationThresh The intensity threshold for region membership. [HU_MIN..HU_MAX]
	 * \param returnImage Already allocated array to return region map.
	 * \return 0 if ok. -1 if size parameter incorrect. -4 if segmentation threshold is incorrect. -5 if data pointer is null. -6 if seed is outside of image. Silent error -99 if size equals 0.
	 */
	SWEIDMT_DLL_IMPORT_EXPORT return_t performRegionGrowing(const image3D &image, const voxel &seed, const short &segmentationThresh, image3D &returnImage);

	/**
	* \brief  Converts voxel position into index.
	*
	* Converts three-dimensional voxel position into one-dimensional index.
	* \param vxl A voxel of a three-dimensional image.
	* \return Index of voxel position.
	*/
	SWEIDMT_DLL_IMPORT_EXPORT int voxel2index(const voxel &vxl);
		
	/**
	* \brief  Converts index into voxel position.
	*
	* Converts one-dimensional index into three-dimensional voxel position.
	* \param index Index of voxel.
	* \return The position of the voxel.
	*/
	SWEIDMT_DLL_IMPORT_EXPORT voxel index2voxel(const int &index);
}


#endif // DLL_HPP_2434312941
