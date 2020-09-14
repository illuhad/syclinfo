/*
 * This file is part of syclinfo, a simple program to query available 
 * SYCL platforms and devices.
 *
 * Copyright (C) 2018  Aksel Alpay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <CL/sycl.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <boost/preprocessor/stringize.hpp>


std::map<cl::sycl::info::device_type, std::string> device_type_representation {
  {cl::sycl::info::device_type::cpu, "CPU"},
  {cl::sycl::info::device_type::gpu, "GPU"},
  {cl::sycl::info::device_type::accelerator, "Accelerator"},
  {cl::sycl::info::device_type::custom, "Custom"},
  {cl::sycl::info::device_type::automatic, "Automatic"},
  {cl::sycl::info::device_type::host, "Host"},
  {cl::sycl::info::device_type::all, "All"}
};
            
std::map<cl::sycl::info::global_mem_cache_type, std::string> global_mem_cache_type_representation {
  {cl::sycl::info::global_mem_cache_type::none, "None"},
  {cl::sycl::info::global_mem_cache_type::read_only, "Read-only"},
  {cl::sycl::info::global_mem_cache_type::write_only, "Write-only"}
};


std::map<cl::sycl::info::local_mem_type, std::string> local_mem_type_representation {
  {cl::sycl::info::local_mem_type::none, "None"},
  {cl::sycl::info::local_mem_type::local, "Local"},
  {cl::sycl::info::local_mem_type::global, "Global"}
};

std::map<cl::sycl::info::fp_config, std::string> fp_config_representation {
  { cl::sycl::info::fp_config::denorm, "denorm"},
  { cl::sycl::info::fp_config::inf_nan, "inf_nan"},
  { cl::sycl::info::fp_config::round_to_nearest, "round_to_nearest"},
  { cl::sycl::info::fp_config::round_to_zero, "round_to_zero"},
  { cl::sycl::info::fp_config::round_to_inf, "round_to_inf"},
  { cl::sycl::info::fp_config::fma, "fma"},
  { cl::sycl::info::fp_config::correctly_rounded_divide_sqrt, "correctly_rounded_divide_sqrt"},
  { cl::sycl::info::fp_config::soft_float, "soft_float" }
};

std::map<cl::sycl::info::execution_capability, std::string> exec_capability_representation{
  {cl::sycl::info::execution_capability::exec_kernel, "exec_kernel"},
  {cl::sycl::info::execution_capability::exec_native_kernel, "exec_native_kernel"}
};


std::map<cl::sycl::info::partition_property, std::string> 
                        partition_property_representation {
  {cl::sycl::info::partition_property::no_partition, "no_partition"},
  {cl::sycl::info::partition_property::partition_equally, "partition_equally"},
  {cl::sycl::info::partition_property::partition_by_counts, "partition_by_counts"},
  {cl::sycl::info::partition_property::partition_by_affinity_domain, "partition_by_affinity_domain"}
};

std::map<cl::sycl::info::partition_affinity_domain, std::string> 
                        partition_affinity_domain_representation {
  {cl::sycl::info::partition_affinity_domain::not_applicable, "not_applicable"},
  {cl::sycl::info::partition_affinity_domain::numa, "numa"},
  {cl::sycl::info::partition_affinity_domain::L4_cache, "L4_cache"},
  {cl::sycl::info::partition_affinity_domain::L3_cache, "L3_cache"},
  {cl::sycl::info::partition_affinity_domain::L2_cache, "L2_cache"},
  {cl::sycl::info::partition_affinity_domain::L1_cache, "L1_cache"},
  {cl::sycl::info::partition_affinity_domain::next_partitionable, "next_partitionable"}
};


template<class T>
std::ostream& operator<<(std::ostream& lhs, const std::vector<T>& rhs)
{
  for(std::size_t i = 0; i < rhs.size(); ++i)
  {
    lhs << rhs[i];
    if (i != rhs.size()-1)
      lhs << ", ";
  }
  return lhs;
}
namespace std{
std::ostream& operator<<(std::ostream& lhs, const cl::sycl::id<3>& idx)
{
  lhs << idx[0] << " " << idx[1] << " " << idx[2];
  return lhs;
}


std::ostream& operator<<(std::ostream& lhs, cl::sycl::info::device_type dtype)
{
  lhs << device_type_representation[dtype];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, cl::sycl::info::global_mem_cache_type cache_type)
{
  lhs << global_mem_cache_type_representation[cache_type];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, cl::sycl::info::local_mem_type local_type)
{
  lhs << local_mem_type_representation[local_type];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, cl::sycl::info::fp_config fpconfig)
{
  lhs << fp_config_representation[fpconfig];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, cl::sycl::info::execution_capability ecap)
{
  lhs << exec_capability_representation[ecap];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, cl::sycl::info::partition_property pprop)
{
  lhs << partition_property_representation[pprop];
  return lhs;
}

std::ostream& operator<<(std::ostream& lhs, cl::sycl::info::partition_affinity_domain domain)
{
  lhs << partition_affinity_domain_representation[domain];
  return lhs;
}
}

#define PRINT_PLATFORM_PROPERTY(plat, prop) \
  std::cout << BOOST_PP_STRINGIZE(prop) << ": " \
            << plat.get_info<cl::sycl::info::platform::prop>() << std::endl;

#define PRINT_DEVICE_PROPERTY(dev, prop) \
  std::cout << BOOST_PP_STRINGIZE(prop) << ": " \
            << dev.get_info<cl::sycl::info::device::prop>() << std::endl;

int main()
{

  std::vector<cl::sycl::device> devices = cl::sycl::device::get_devices();

  for(const auto& dev : devices)
  {
    std::cout << "***************************************" << std::endl;
    std::cout << "           Platform:                   " << std::endl;
    std::cout << "***************************************" << std::endl;

    cl::sycl::platform plat = dev.get_platform();

    PRINT_PLATFORM_PROPERTY(plat, name);
    PRINT_PLATFORM_PROPERTY(plat, vendor);
    PRINT_PLATFORM_PROPERTY(plat, version);
    PRINT_PLATFORM_PROPERTY(plat, profile);
    PRINT_PLATFORM_PROPERTY(plat, extensions);
    
    std::cout << "============ Found device: =============" << std::endl;
    PRINT_DEVICE_PROPERTY(dev, name);
    PRINT_DEVICE_PROPERTY(dev, vendor);
    PRINT_DEVICE_PROPERTY(dev, driver_version);
    PRINT_DEVICE_PROPERTY(dev, profile);
    PRINT_DEVICE_PROPERTY(dev, version);
    PRINT_DEVICE_PROPERTY(dev, opencl_c_version);
    PRINT_DEVICE_PROPERTY(dev, extensions);
    PRINT_DEVICE_PROPERTY(dev, device_type);
    PRINT_DEVICE_PROPERTY(dev, vendor_id);
    PRINT_DEVICE_PROPERTY(dev, max_compute_units);
    PRINT_DEVICE_PROPERTY(dev, max_work_item_dimensions);
    PRINT_DEVICE_PROPERTY(dev, max_work_item_sizes);
    PRINT_DEVICE_PROPERTY(dev, max_work_group_size);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_char);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_short);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_int);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_long);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_float);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_double);
    PRINT_DEVICE_PROPERTY(dev, preferred_vector_width_half);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_char);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_short);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_int);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_long);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_float);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_double);
    PRINT_DEVICE_PROPERTY(dev, native_vector_width_half);
    PRINT_DEVICE_PROPERTY(dev, max_clock_frequency);
    PRINT_DEVICE_PROPERTY(dev, address_bits);
    PRINT_DEVICE_PROPERTY(dev, max_mem_alloc_size);
    PRINT_DEVICE_PROPERTY(dev, image_support);
    PRINT_DEVICE_PROPERTY(dev, max_read_image_args);
    PRINT_DEVICE_PROPERTY(dev, max_write_image_args);
    PRINT_DEVICE_PROPERTY(dev, image2d_max_height);
    PRINT_DEVICE_PROPERTY(dev, image2d_max_width);
    PRINT_DEVICE_PROPERTY(dev, image3d_max_height);
    PRINT_DEVICE_PROPERTY(dev, image3d_max_width);
    PRINT_DEVICE_PROPERTY(dev, image3d_max_depth);
    PRINT_DEVICE_PROPERTY(dev, image_max_buffer_size);
    PRINT_DEVICE_PROPERTY(dev, image_max_array_size);
    PRINT_DEVICE_PROPERTY(dev, max_samplers);
    PRINT_DEVICE_PROPERTY(dev, max_parameter_size);
    PRINT_DEVICE_PROPERTY(dev, mem_base_addr_align);
    
    PRINT_DEVICE_PROPERTY(dev, half_fp_config);
    PRINT_DEVICE_PROPERTY(dev, single_fp_config);
    PRINT_DEVICE_PROPERTY(dev, double_fp_config);
    PRINT_DEVICE_PROPERTY(dev, global_mem_cache_type);
    PRINT_DEVICE_PROPERTY(dev, global_mem_cache_line_size);
    PRINT_DEVICE_PROPERTY(dev, global_mem_cache_size);
    PRINT_DEVICE_PROPERTY(dev, global_mem_size);
    PRINT_DEVICE_PROPERTY(dev, max_constant_buffer_size);
    PRINT_DEVICE_PROPERTY(dev, max_constant_args);
    PRINT_DEVICE_PROPERTY(dev, local_mem_type);
    PRINT_DEVICE_PROPERTY(dev, local_mem_size);
    PRINT_DEVICE_PROPERTY(dev, error_correction_support);
    PRINT_DEVICE_PROPERTY(dev, host_unified_memory);
    PRINT_DEVICE_PROPERTY(dev, profiling_timer_resolution);
    PRINT_DEVICE_PROPERTY(dev, is_endian_little);
    PRINT_DEVICE_PROPERTY(dev, is_available);
    PRINT_DEVICE_PROPERTY(dev, is_compiler_available);
    PRINT_DEVICE_PROPERTY(dev, is_linker_available);
    PRINT_DEVICE_PROPERTY(dev, execution_capabilities);
    PRINT_DEVICE_PROPERTY(dev, queue_profiling);
    PRINT_DEVICE_PROPERTY(dev, built_in_kernels);
    
    
    PRINT_DEVICE_PROPERTY(dev, printf_buffer_size);
    PRINT_DEVICE_PROPERTY(dev, preferred_interop_user_sync);
    PRINT_DEVICE_PROPERTY(dev, partition_max_sub_devices);
    
    PRINT_DEVICE_PROPERTY(dev, partition_properties);
    PRINT_DEVICE_PROPERTY(dev, partition_affinity_domains);
    PRINT_DEVICE_PROPERTY(dev, partition_type_property);
    PRINT_DEVICE_PROPERTY(dev, partition_type_affinity_domain);
    PRINT_DEVICE_PROPERTY(dev, reference_count);               

    std::cout << std::endl << std::endl;
  }
}
