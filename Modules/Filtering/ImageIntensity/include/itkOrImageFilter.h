/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkOrImageFilter_h
#define itkOrImageFilter_h

#include "itkBinaryFunctorImageFilter.h"
#include "itkNumericTraits.h"

namespace itk
{
namespace Functor
{
/**
 * \class OR
 * \brief bitwise OR functor
 * \ingroup ITKImageIntensity
 */
template< typename TInput1, typename TInput2 = TInput1, typename TOutput = TInput1 >
class OR
{
public:
  OR() {}
  ~OR() {}
  bool operator!=(const OR &) const
  {
    return false;
  }

  bool operator==(const OR & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput1 & A, const TInput2 & B) const
  {
    return static_cast< TOutput >( A | B );
  }
};
}
/** \class OrImageFilter
 * \brief Implements the OR bitwise operator pixel-wise between two images.
 *
 * This class is templated over the types of the two
 * input images and the type of the output image.
 * Numeric conversions (castings) are done by the C++ defaults.
 *
 * Since the bitwise OR operation is only defined in C++ for integer
 * types, the images passed to this filter must comply with the requirement
 * of using integer pixel type.
 *
 * The total operation over one pixel will be
 *
 * \code
 *  output_pixel = static_cast<OutputPixelType>( input1_pixel | input2_pixel )
 * \endcode
 *
 * Where "|" is the boolean OR operator in C++.
 *
 * \ingroup IntensityImageFilters
 * \ingroup MultiThreaded
 * \ingroup ITKImageIntensity
 *
 * \wiki
 * \wikiexample{ImageProcessing/OrImageFilter,Binary OR two images}
 * \endwiki
 */
template< typename TInputImage1, typename TInputImage2 = TInputImage1, typename TOutputImage = TInputImage1 >
class OrImageFilter:
  public
  BinaryFunctorImageFilter< TInputImage1, TInputImage2, TOutputImage,
                            Functor::OR<
                              typename TInputImage1::PixelType,
                              typename TInputImage2::PixelType,
                              typename TOutputImage::PixelType >   >

{
public:
  /** Standard class typedefs. */
  typedef OrImageFilter Self;
  typedef BinaryFunctorImageFilter<
    TInputImage1, TInputImage2, TOutputImage,
    Functor::OR< typename TInputImage1::PixelType,
                 typename TInputImage2::PixelType,
                 typename TOutputImage::PixelType > > Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(OrImageFilter,
               BinaryFunctorImageFilter);

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( Input1Input2OutputBitwiseOperatorsCheck,
                   ( Concept::BitwiseOperators< typename TInputImage1::PixelType,
                                                typename TInputImage2::PixelType,
                                                typename TOutputImage::PixelType > ) );
  // End concept checking
#endif

protected:
  OrImageFilter() {}
  virtual ~OrImageFilter() {}

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(OrImageFilter);
};
} // end namespace itk

#endif
