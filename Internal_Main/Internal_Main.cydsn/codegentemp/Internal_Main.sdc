# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\samue\OneDrive\Documents\GitHub\Li-CellTesting_Script\Internal_Main\Internal_Main.cydsn\Internal_Main.cyprj
# Date: Thu, 13 May 2021 06:24:52 GMT
#set_units -time ns
create_clock -name {ADC_1_intSarClock(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_12}]]
create_clock -name {I2C_1_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_0}]]
create_clock -name {UART_1_SCBCLK(FFB)} -period 708.33333333333326 -waveform {0 354.166666666667} [list [get_pins {ClockBlock/ff_div_1}]]
create_clock -name {Clock_2(FFB)} -period 62500 -waveform {0 31250} [list [get_pins {ClockBlock/ff_div_4}]]
create_clock -name {Clock_1(FFB)} -period 7812500 -waveform {0 3906250} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyILO} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {ADC_1_intSarClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list]
create_generated_clock -name {I2C_1_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 15 31} [list]
create_generated_clock -name {UART_1_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 35} -nominal_period 708.33333333333326 [list]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 1501 3001} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 187501 375001} [list]


# Component constraints for C:\Users\samue\OneDrive\Documents\GitHub\Li-CellTesting_Script\Internal_Main\Internal_Main.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\samue\OneDrive\Documents\GitHub\Li-CellTesting_Script\Internal_Main\Internal_Main.cydsn\Internal_Main.cyprj
# Date: Thu, 13 May 2021 06:24:49 GMT
