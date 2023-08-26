#![no_main]
#![no_std]

use panic_rtt_target as _;

use stm32f7xx_hal::prelude::*;
use cortex_m_rt::entry;


#[entry]
fn main() -> ! {
    loop {
    }
}
