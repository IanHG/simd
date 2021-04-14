#include <benchmark/benchmark.h>

#include <numeric>
#include <complex>

#include "../../simd.hpp"

template
   <  typename T
   >
struct is_complex : std::false_type {};

template
   <  typename T
   >
struct is_complex<std::complex<T>> : std::true_type {};

template<typename T> inline constexpr bool is_complex_v = is_complex<T>::value;

template
   <  typename T
   ,  std::enable_if_t<is_complex_v<T> >* = nullptr
   >
inline constexpr T Conj
   (  const T& v
   )
{
   return std::conj(v);
}
template
   <  typename T
   ,  std::enable_if_t<!is_complex_v<T> >* = nullptr
   >
inline constexpr T Conj
   (  const T& v
   )
{
   return v;
}

template
   <  typename RET_T
   ,  typename VEC_T
   >
RET_T dot_product_impl
   (  const VEC_T& aLeft
   ,  const VEC_T& aRight
   )
{
   // Allow for custom begin, end, advance, and distance by using ADL
   using std::begin;
   using std::end;
   using std::advance;
   using std::distance;
   using ret_t = RET_T;
   ret_t result1 = 0;
   ret_t result2 = 0;
   auto lit1 = begin(aLeft);
   auto lit2 = begin(aLeft); advance(lit2, 1);
   auto rit1 = begin(aRight);
   auto rit2 = begin(aRight); advance(rit2, 1);
   auto lend = end(aLeft);
   auto dist = distance(lit1, lend);
   // For even number of data, lit1 will hit lend
   if (  dist % 2 == 0
      )
   {
      for(; lit1 != lend; advance(lit1, 2), advance(lit2, 2), advance(rit1, 2), advance(rit2, 2))
      {
         result1 += Conj(*lit1) * *rit1;
         result2 += Conj(*lit2) * *rit2;
      }
   }
   // For odd number, lit2 will hit end, but the last element of beg1 will need to be added after the loop
   else
   {
      for(; lit2 != lend; advance(lit1, 2), advance(lit2, 2), advance(rit1, 2), advance(rit2, 2))
      {
         result1 += Conj(*lit1) * *rit1;
         result2 += Conj(*lit2) * *rit2;
      }
      result1 += Conj(*lit1) * *rit1;
   }
   return result1 + result2;
}

template<class T>
T dot(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
   T dot_result = static_cast<T>(0.0);

   for(int i = 0; i < static_cast<int>(vec1.size()); ++i)
   {
      dot_result += vec1[i] * vec2[i];
   }

   return dot_result;
}

template<class T>
T dot_iterator(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
   T dot_result = static_cast<T>(0.0);
   
   auto iter1 = vec1.begin();
   auto iter2 = vec2.begin();

   for(; iter1 != vec1.end(); ++iter1, ++iter2)
   {
      dot_result += (*iter1) * (*iter2);
   }

   return dot_result;
}

template<class T>
T dot(const T* const vec1, const T* const vec2, int size)
{
   T dot_result = static_cast<T>(0.0);

   for(int i = 0; i < size; ++i)
   {
      dot_result += vec1[i] * vec2[i];
   }

   return dot_result;
}

template<class T>
T dot_restrict(const T* const __restrict vec1, const T* const __restrict vec2, int size)
{
   T dot_result = static_cast<T>(0.0);

   for(int i = 0; i < size; ++i)
   {
      dot_result += vec1[i] * vec2[i];
   }

   return dot_result;
}

static void Benchmark_vector(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   std::vector<double> vec1(N, 1.1);
   std::vector<double> vec2(N, 1.2);
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = dot(vec1, vec2));
   }
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_vector)->DenseRange(8, 16);

static void Benchmark_vector_iterator(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   std::vector<double> vec1(N, 1.1);
   std::vector<double> vec2(N, 1.2);
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = dot_iterator(vec1, vec2));
   }
}

/* Run benchmark for I in [8; 16] */
//BENCHMARK(Benchmark_vector_iterator)->DenseRange(8, 16);

static void Benchmark_pointer(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   double* vec1 = new double[N];
   double* vec2 = new double[N];

   for(int i = 0; i < N; ++i)
   {
      vec1[i] = 1.1;
      vec2[i] = 1.2;
   }
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = dot(vec1, vec2, N));
   }

   delete[] vec1;
   delete[] vec2;
}

/* Run benchmark for I in [8; 16] */
//BENCHMARK(Benchmark_pointer)->DenseRange(8, 16);

static void Benchmark_pointer_restrict(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   double* vec1 = new double[N];
   double* vec2 = new double[N];

   for(int i = 0; i < N; ++i)
   {
      vec1[i] = 1.1;
      vec2[i] = 1.2;
   }
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = dot_restrict(vec1, vec2, N));
   }

   delete[] vec1;
   delete[] vec2;
}

/* Run benchmark for I in [8; 16] */
//BENCHMARK(Benchmark_pointer_restrict)->DenseRange(8, 16);

static void Benchmark_dot_product_impl(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   std::vector<double> vec1(N, 1.1);
   std::vector<double> vec2(N, 1.2);
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = dot_product_impl<double>(vec1, vec2));
   }
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_dot_product_impl)->DenseRange(8, 16);

static void Benchmark_std_inner_product(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   std::vector<double> vec1(N, 1.1);
   std::vector<double> vec2(N, 1.2);
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), static_cast<double>(0.0)));
   }
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_std_inner_product)->DenseRange(8, 16);

static void Benchmark_std_transform_reduce(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   std::vector<double> vec1(N, 1.1);
   std::vector<double> vec2(N, 1.2);
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = std::transform_reduce(vec1.begin(), vec1.end(), vec2.begin(), static_cast<double>(0.0)));
   }
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_std_transform_reduce)->DenseRange(8, 16);

static void Benchmark_simd_avx2_256_pdot_float64(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   double* vec1 = (double*)simd_allocate(N * sizeof(double));
   double* vec2 = (double*)simd_allocate(N * sizeof(double));

   for(int i = 0; i < N; ++i)
   {
      vec1[i] = 1.1;
      vec2[i] = 1.2;
   }
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = avx2_256_pdot_float64(vec1, vec2, N));
   }

   simd_deallocate(vec1);
   simd_deallocate(vec2);
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_simd_avx2_256_pdot_float64)->DenseRange(8, 16);

static void Benchmark_simd_avx2_256_pdot_float64_align32(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   double* vec1 = (double*)simd_allocate(N * sizeof(double));
   double* vec2 = (double*)simd_allocate(N * sizeof(double));

   for(int i = 0; i < N; ++i)
   {
      vec1[i] = 1.1;
      vec2[i] = 1.2;
   }
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = avx2_256_pdot_float64_align32(vec1, vec2, N));
   }

   simd_deallocate(vec1);
   simd_deallocate(vec2);
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_simd_avx2_256_pdot_float64_align32)->DenseRange(8, 16);

static void Benchmark_simd_avx2_256_pdot_float64_align32_accu2(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   double* vec1 = (double*)simd_allocate(N * sizeof(double));
   double* vec2 = (double*)simd_allocate(N * sizeof(double));

   for(int i = 0; i < N; ++i)
   {
      vec1[i] = 1.1;
      vec2[i] = 1.2;
   }
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = avx2_256_pdot_float64_align32_accu2(vec1, vec2, N));
   }

   simd_deallocate(vec1);
   simd_deallocate(vec2);
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_simd_avx2_256_pdot_float64_align32_accu2)->DenseRange(8, 16);

static void Benchmark_simd_avx2_256_pdot_float64_align32_accu4(benchmark::State& s)
{
   // Create 2^I samples
   int N = 1 << s.range(0);

   double* vec1 = (double*)simd_allocate(N * sizeof(double));
   double* vec2 = (double*)simd_allocate(N * sizeof(double));

   for(int i = 0; i < N; ++i)
   {
      vec1[i] = 1.1;
      vec2[i] = 1.2;
   }
   
   double d;
   while(s.KeepRunning())
   {
      benchmark::DoNotOptimize(d = avx2_256_pdot_float64_align32_accu4(vec1, vec2, N));
   }

   simd_deallocate(vec1);
   simd_deallocate(vec2);
}

/* Run benchmark for I in [8; 16] */
BENCHMARK(Benchmark_simd_avx2_256_pdot_float64_align32_accu4)->DenseRange(8, 16);

/* Create main()-function */
BENCHMARK_MAIN();
