use std::collections::HashMap;

macro_rules! unwrap_or_return {
    ($o:expr) => {
        match $o {
            Some(r) => r,
            None => {return vec![]}
        }
    }
}

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut precompute : HashMap<i32, i32> = HashMap::<i32, i32>::new();
        for i in 0..nums.len() {
            let val = *unwrap_or_return!(nums.get(i));
            let compute = target - val;
            
            let i = i as i32;
            match precompute.get(&compute) {
                Some(idx) => {return vec![*idx, i];}
                None => {precompute.insert(val, i);}
            }
        }
        return vec![-1, -1];
    }
}