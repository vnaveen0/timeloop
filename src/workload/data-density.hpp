/* Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <bitset>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace problem
{

// notes for future improvements
// this class should be more general, statiscal modeling focused, and directly produces the following
//    (1) largest density of the tile (for the occupancy check and slowest compute unit)
//    (2) smallest density of the tile
//    (3) avgerage density of the tile 
// the interface should invovle coordinate dependent setup, i.e., where is the tile in the workload
// the other parts of the infrastructure should be independent from the distribution format

struct DataDensity{ 

  double average_density_ = 1.0;
  double variance_ = 0.0;

  DataDensity(){
    average_density_ = 1;  // default density to 1
  }
  
  DataDensity(const double& average_density){
    average_density_ = average_density;
  }

  DataDensity(const double& average_density, const double& variance){
    average_density_ = average_density;
    variance_ = variance;
  }

  double GetAverageDensity() const {
    return average_density_;
  }

  double GetVariance() const {
    return variance_;
  }

  // Serialization.
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version=0){
    if (version == 0)
     { 
       ar& BOOST_SERIALIZATION_NVP(average_density_);
       ar& BOOST_SERIALIZATION_NVP(variance_);
     }
  }
}; // struct
} // namespace