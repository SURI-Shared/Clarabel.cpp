#pragma once

#include <Eigen/Eigen>
#include <cstdint>
#include <type_traits>

namespace clarabel
{

enum class SolverStatus
{
    Unsolved,
    Solved,
    PrimalInfeasible,
    DualInfeasible,
    AlmostSolved,
    AlmostPrimalInfeasible,
    AlmostDualInfeasible,
    MaxIterations,
    MaxTime,
    NumericalError,
    ScalingError,
    InsufficientProgress,
};

template<typename T = double>
class DefaultSolution
{
    static_assert(std::is_same<T, float>::value || std::is_same<T, double>::value, "T must be float or double");

  public:
    struct ClarabelDefaultSolution
    {
        T *x;
        uintptr_t x_length;
        T *z;
        uintptr_t z_length;
        T *s;
        uintptr_t s_length;
        SolverStatus status;
        T obj_val;
        T obj_val_dual;
        double solve_time;
        double setup_time;
        double equilibration_time;
        double kktinit_time;
        double initialization_time;
        double ip_iteration_time;
        double kkt_update_time;
        double kkt_solve_time;
        uint32_t iterations;
        T r_prim;
        T r_dual;

        // T **xhist;
        // T **zhist;
        // T **shist;
    };

    Eigen::Map<Eigen::VectorX<T>> x, z, s;
    SolverStatus status;
    T obj_val;
    T obj_val_dual;
    double solve_time;
    double setup_time;
    double equilibration_time;
    double kktinit_time;
    double initialization_time;
    double ip_iteration_time;
    double kkt_update_time;
    double kkt_solve_time;
    uint32_t iterations;
    T r_prim;
    T r_dual;

    // std::vector<Eigen::Map<Eigen::VectorX<T>>> xhist,zhist,shist;

    DefaultSolution(ClarabelDefaultSolution &solution)
        : 
        x(solution.x, solution.x_length), 
        z(solution.z, solution.z_length), 
        s(solution.s, solution.s_length),
        status(solution.status), 
        obj_val(solution.obj_val),
        obj_val_dual(solution.obj_val_dual),
        solve_time(solution.solve_time),
        setup_time(solution.setup_time),
        equilibration_time(solution.equilibration_time),
        kktinit_time(solution.kktinit_time),
        initialization_time(solution.initialization_time),
        ip_iteration_time(solution.ip_iteration_time),
        kkt_update_time(solution.kkt_update_time),
        kkt_solve_time(solution.kkt_solve_time),
        iterations(solution.iterations),
        r_prim(solution.r_prim), 
        r_dual(solution.r_dual)
        // xhist(iterations),
        // zhist(iterations),
        // shist(iterations)
    {
        // for(size_t i=0;i<iterations;i++){
        //     xhist.emplace_back(solution.xhist[i],solution.x_length);
        //     zhist.emplace_back(solution.zhist[i],solution.z_length);
        //     shist.emplace_back(solution.shist[i],solution.s_length);
        // }
    }
    DefaultSolution():x(nullptr,0),z(nullptr,0),s(nullptr,0),status(SolverStatus::Unsolved),obj_val(0),obj_val_dual(0),solve_time(0),iterations(0),r_prim(0),r_dual(0){}//dangerous nullptr!
};

// Instantiate the templates
template struct DefaultSolution<double>;
template struct DefaultSolution<float>;

} // namespace clarabel