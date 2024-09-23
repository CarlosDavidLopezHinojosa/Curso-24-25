#ifndef ALGORITHMICS_UTILS_IMPL_HPP
#define ALGORITHMICS_UTILS_IMPL_HPP

#include "algorithmics_utils.hpp"

/**
 * @brief Implementation for the base class PolynomialComplexity
 */
template <class R, typename... Args>
PolynomialComplexity<R, Args...>::PolynomialComplexity(std::function<R(Args&...)> algorithm, 
                                     std::function<std::tuple<Args&...>(int)> rand_gen,
                                     int polynomial_degree)
{
    mean_[0] = mean_[1] = 0.0;
    variance_[0] = variance_[1] = 0.0;
    is_executed_ = false;
    algorithm_ = algorithm;
    rand_gen_ = rand_gen;
    coeficients_.resize(polynomial_degree + 1);
}

template <class R, typename... Args>
double PolynomialComplexity<R, Args...>::real_mean() const { return mean_[0]; }

template <class R, typename... Args>
double PolynomialComplexity<R, Args...>::real_variance() const { return variance_[0]; }

template <class R, typename... Args>
double PolynomialComplexity<R, Args...>::real_std_dev() const { return (std::sqrt(real_variance())); }

template <class R, typename... Args>
double PolynomialComplexity<R, Args...>::calculated_mean() const { return mean_[1]; }

template <class R, typename... Args>
double PolynomialComplexity<R, Args...>::calculated_variance() const { return variance_[1]; }

template <class R, typename... Args>
double PolynomialComplexity<R, Args...>::calculated_std_dev() const { return (std::sqrt(calculated_variance())); }

template <class R, typename... Args>
double PolynomialComplexity<R, Args...>::determinance() const 
{ 
    assert(is_executed()); 
    return static_cast<double>(calculated_std_dev()/real_std_dev()); 
}

template <class R, typename... Args>
bool PolynomialComplexity<R, Args...>::is_executed() const { return is_executed_; }

template <class R, typename... Args>
void PolynomialComplexity<R, Args...>::set_executed(bool state) { is_executed_ = state; }

template <class R, typename... Args>
void PolynomialComplexity<R, Args...>::load_datafile(const std::string& file_name)
{
    std::ofstream file(file_name);
    if (!file.is_open())
        std::cerr << "File " << file_name << "couldn't be properly opened \n";

    for (size_t i = 0; i < times.size(); i++)
        file << size_at(i) << " " << time_at(i) << "\n";
    
    file.close();
}


/**
 * @brief Implementation for QuadraticComplexity class
 */
template <class R, typename... Args>
void PolynomialComplexity<R, Args...>::calculate_complexity(int min_size, int max_size, int iterations)
{
    std::random_device size_seed;
    std::mt19937 size_generator(size_seed());
    std::uniform_int_distribution<int> size_distribution(min_size,max_size);

    Clock c;

    Eigen::MatrixXd A(iterations, 3);
    Eigen::VectorXd X(iterations);
    Eigen::VectorXd coef(3);

    set_sizes(iterations);
    set_times(iterations);

    for (size_t i = 0; i < size_t(iterations); i++)
    {
        int random_size = size_distribution(size_generator);

        std::tuple<Args&...> args = generate(random_size);

        c.start();
        apply(args);
        c.stop();

        uint64_t time_elapsed = c.elapsed();

        size_at(i) = random_size;
        time_at(i) = time_elapsed;

        double n = static_cast<double>(random_size);

        for (size_t j = 0; j < polynomial_degree() + 1; j++)
            A(i,j) = std::pow(n,polynomial_degree() - j);
        
        X(i) = static_cast<double>(time_elapsed);
    }

    coef = A.colPivHouseholderQr().solve(X);

    for (size_t i = 0; i < polynomial_degree(); i++)
        coeficient(i) = coef(i);
    
    set_executed(true);
}

template <class R, typename... Args>
uint64_t PolynomialComplexity<R, Args...>::estimation(int n)
{
    assert(is_executed());
    uint64_t est = uint64_t();

    for (size_t i = 0; i < polynomial_degree() + 1; i++)
        est += std::pow(n,polynomial_degree() -  i) * coeficient(i);
    
    return est;
}


template <class R, typename... Args>
void PolynomialComplexity<R, Args...>::calculate_statistics()
{
    assert(is_executed());

    size_t n = sizes.size();
    Eigen::VectorXd real_times(n);
    Eigen::VectorXd calc_times(n);

    for (size_t i = 0; i < n; i++)
        real_times(i) = static_cast<double>(time_at(i));
    
    for (size_t i = 0; i < n; i++)
        calc_times(i) = estimation(size_at(i));
    
    double real_mean = real_times.mean();
    double calc_mean = calc_times.mean();

    double real_variance = (real_times.array() - real_mean).square().mean();
    double calc_variance = (calc_times.array() - calc_mean).square().mean();

    set_real_mean(real_mean);
    set_calculated_mean(calc_mean);
    set_real_variance(real_variance);
    set_calculated_variance(calc_variance);
}
#endif