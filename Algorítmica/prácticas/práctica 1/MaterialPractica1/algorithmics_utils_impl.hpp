#ifndef ALGORITHMICS_UTILS_IMPL_HPP
#define ALGORITHMICS_UTILS_IMPL_HPP

#include "algorithmics_utils.hpp"

/**
 * This is the implementation of the base class OComplexity, which we will use in every complexity scenario
 */
template <class T, typename Func>
OComplexity<T,Func>::OComplexity(Func algorithm)
{
    median_[0] = median_[1] = 0.0d;
    variance_[0] = variance_[1] = 0.0d;
    is_executed_ = false;
    algorithm_ = algorithm;
}

template <class T, typename Func>
double OComplexity<T,Func>::real_median() const { return median_[0]; }

template <class T, typename Func>
double OComplexity<T,Func>::real_variance() const { return variance_[0]; }

template <class T, typename Func>
double OComplexity<T,Func>::real_std_dev() const { return (std::sqrt(real_variance())); }

template <class T, typename Func>
double OComplexity<T,Func>::calculated_median() const { return median_[1]; }

template <class T, typename Func>
double OComplexity<T,Func>::calculated_variance() const { return variance_[1]; }

template <class T, typename Func>
double OComplexity<T,Func>::calculated_std_dev() const { return (std::sqrt(calculated_variance())); }

template <class T, typename Func>
double OComplexity<T,Func>::determinance() const { return static_cast<double>(calculated_variance()/real_variance()); }

template <class T, typename Func>
bool OComplexity<T,Func>::is_executed() const { return is_executed_; }

template <class T, typename Func>
void OComplexity<T,Func>::set_executed(bool state) { is_executed_ = state; }

template <class T, typename Func>
void OComplexity<T,Func>::load_datafile(std::string file_name)
{
    std::ofstream file(file_name);
    if (!file.is_open())
        std::cerr << "Error no se pudo abrir el fichero de datos " << file_name << "\n";
    
    auto& t = this->times;
    auto& s  = this->sizes;

    std::sort(t.begin(),t.end());
    std::sort(s.begin(),s.end());

    for (size_t i = 0; i < this->times.size(); i++)
        file << size_at(i) << " " << time_at(i) << "\n";
    
    file.close();
}


template <class T, typename Func>
std::vector<T> QuadraticComplexity<T,Func>::generate_random_vector(int tam, T min, T max)
{
    std::random_device value_seed;
    std::mt19937 value_generator(value_seed());
    std::uniform_int_distribution<T> value_distribution(min,max);

    std::vector<T> v(tam);

    for (size_t i = 0; i < size_t(tam); i++)
        v[i] = value_distribution(value_generator);

    return v;
}


/**
 * This is implementation for the derived class for square polynomial time complexity Algorithms
 */
template <class T, typename Func>
void QuadraticComplexity<T,Func>::calculate_complexity(int max_size, int min_size, int iterations)
{
    assert(max_size > min_size && iterations > 0);

    std::random_device size_seed;
    std::mt19937 size_generator(size_seed());
    std::uniform_int_distribution<int> size_distribution(min_size,max_size);

    Clock c;

    Eigen::MatrixXd A(iterations,3);
    Eigen::VectorXd X(iterations);
    Eigen::VectorXd coef(3);

    this->set_sizes(iterations);
    this->set_times(iterations);

    for (size_t i = 0; i < size_t(iterations); i++)
    {
        int random_size = size_distribution(size_generator);
        std::vector<T> v(generate_random_vector(random_size,min_size,max_size));

        c.start();
        this->apply()(v);
        c.stop();

        uint64_t time_elapsed = c.elapsed();

        this->size_at(i) = random_size;
        this->time_at(i) = time_elapsed;

        double n = static_cast<double>(random_size);

        A(i,0) = n*n;
        A(i,1) = n;
        A(i,2) = 1.0;

        X(i) = static_cast<double>(time_elapsed);
    }    


    coef = A.colPivHouseholderQr().solve(X);

    coeficient(0) = coef(0);
    coeficient(1) = coef(1);
    coeficient(2) = coef(2);
    this->set_executed(true);

}

template <class T, typename Func>
uint64_t QuadraticComplexity<T,Func>::estimation(int n)
{
    assert(this->is_executed());
    return static_cast<uint64_t>(coeficient(0)*n*n + coeficient(1)*n + coeficient(2));
}

template <class T, typename Func>
void QuadraticComplexity<T,Func>::calculate_statistics()
{
    assert(this->is_executed());

    size_t n = this->sizes.size();
    Eigen::VectorXd real_times(n);
    Eigen::VectorXd calc_times(n);

    for (size_t i = 0; i < n; i++)
        real_times(i) = static_cast<double>(this->time_at(i));
    

    for (size_t i = 0; i < n; i++)
        calc_times(i) = estimation(this->size_at(i));
    

    double real_median, calc_median;
    double real_variance, calc_variance;

    real_median = real_times.mean();
    calc_median = calc_times.mean();

    real_variance = (real_times.array() - real_median).square().mean();
    calc_variance = (calc_times.array() - calc_median).square().mean();


    this->set_real_median(real_median);
    this->set_calculated_median(calc_median);
    this->set_real_variance(real_variance);
    this->set_calculated_variance(calc_variance);
}

#endif