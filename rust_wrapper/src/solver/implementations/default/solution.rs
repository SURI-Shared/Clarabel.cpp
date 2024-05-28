use super::solver::ClarabelSolverStatus;
use clarabel::algebra::FloatT;
use clarabel::solver as lib;

#[repr(C)]
pub struct DefaultSolution<T: FloatT> {
    pub x: *mut T,
    pub x_length: usize,

    pub z: *mut T,
    pub z_length: usize,

    pub s: *mut T,
    pub s_length: usize,

    pub status: ClarabelSolverStatus,
    pub obj_val: T,
    pub obj_val_dual: T,
    pub solve_time: f64,
    pub setup_time: f64,
    pub equilibration_time: f64,
    pub kktinit_time: f64,
    pub initialization_time: f64,
    pub ip_iteration_time: f64,
    pub kkt_update_time: f64,
    pub kkt_solve_time: f64,
    pub iterations: u32,
    pub r_prim: T,
    pub r_dual: T,

    // // old iterates
    // pub xhist: *mut *mut T,
    // pub zhist: *mut *mut T,
    // pub shist: *mut *mut T,

}

impl<T: FloatT> DefaultSolution<T> {
    pub fn from(solution: &mut lib::DefaultSolution<T>) -> Self {
        // let mut xptrs=Vec::with_capacity(solution.xhist.len());
        // let mut zptrs=Vec::with_capacity(solution.zhist.len());
        // let mut sptrs=Vec::with_capacity(solution.shist.len());
        // for i in 0..solution.xhist.len(){
        //     let entry=solution.xhist.get_mut(i);
        //     match entry{
        //         Some(e)=>{xptrs.push(e.as_mut_ptr())}
        //         None=>{}
        //     }
        // }
        // for i in 0..solution.zhist.len(){
        //     let entry=solution.zhist.get_mut(i);
        //     match entry{
        //         Some(e)=>{zptrs.push(e.as_mut_ptr())}
        //         None=>{}
        //     }
        // }
        // for i in 0..solution.shist.len(){
        //     let entry=solution.shist.get_mut(i);
        //     match entry{
        //         Some(e)=>{sptrs.push(e.as_mut_ptr())}
        //         None=>{}
        //     }
        // }
        Self {
            x: solution.x.as_mut_ptr(),
            x_length: solution.x.len(),
            z: solution.z.as_mut_ptr(),
            z_length: solution.z.len(),
            s: solution.s.as_mut_ptr(),
            s_length: solution.s.len(),
            status: ClarabelSolverStatus::from(&mut solution.status),
            obj_val: solution.obj_val,
            obj_val_dual: solution.obj_val_dual,
            solve_time: solution.solve_time,
            setup_time: solution.timings["setup"],
            equilibration_time: solution.timings["equilibration"],
            kktinit_time: solution.timings["kktinit"],
            initialization_time: solution.timings["initialization"],
            ip_iteration_time: solution.timings["IP iteration"],
            kkt_update_time: solution.timings["kkt update"],
            kkt_solve_time: solution.timings["kkt solve"],
            iterations: solution.iterations,
            r_prim: solution.r_prim,
            r_dual: solution.r_dual,
            // xhist:xptrs.as_mut_ptr(),
            // zhist: zptrs.as_mut_ptr(),
            // shist: sptrs.as_mut_ptr()
        }
    }
}
