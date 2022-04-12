# Report

### GitHub repo
https://github.com/YU-LIN-LIN/ESL_HW3

## First Part

### General description or introduction of the problem and your solution
	In this homework, I design a synthesizable verdion of the Gaussian blur module.
	Doing basic HLS (without optimization), and other optimized HLS offered by stratus HLS like loop-unrolling, data path optimization and pipeline.
	
### Implementation details
	timing	lat_min	lat_max	hls_config	loop_unroll	initiation interval	latency		area
	20	0	3	BASIC		X		X			20		2253.6	
	20	0	3	DPA		X		X			29		1813.4	
	10	0	3	BASIC		X		X			20		2253.6	
	10	0	3	DPA		X		X			29		1813.4	
	10	0	3	DPAUA		V		X			21		2856.5	
	10	0	3	PIPELINE	X		1			1		7554.2
	10	0	3	PIPELINE	X		2			2		6457.4	
	10	0	3	PIPELINE	X		3			3		5362.1	
### Additional features of your design and models

	If the cycle time is met, set higher cycle time will not affect the HLS result.
	Optimizing with data path optimization will make area smaller, however it also increase a few latency.
	Unroll the loop will make the latency lower. The HLS result also tell us this.
	Optimizing with pipeline could decrease latency a lot, but the area will become much larger at the same time. 

### Experimental results
	Total cycles of 'hls_config' = 'BASIC' 		: 1310719 cycles
	Total cycles of 'hls_config' = 'DPA'  		: 1900543 cycles
	Total cycles of 'hls_config' = 'DPAUA'		: 1376255 cycles
	Total cycles of 'hls_config' = 'PIPELINE' 	: 65554   cycles	(initial interval = 1)
	Total cycles of 'hls_config' = 'PIPELINE' 	: 131089  cycles	(initial interval = 2)
	Total cycles of 'hls_config' = 'PIPELINE' 	: 196624  cycles	(initial interval = 3)

### Discussions and conclusions
	At first, I changed the (min, max) value of latency constaint from (0, 1) to (0, 3). Or the cycle time needs to set really large to make HLS be successful.
	In this homework, we can make the latency 20 times lower with just 2 times larger in area. I think it is a valuable tradeoff.

## Second Part
	After BASIC HLS, I knew the latency of Gaussian Filter without pipeline is 20 cycles, and the total simulated time is 14548992 ns. It is not the same with the result of BASIC HLS, whose total simulated time is 13107250. I guess it is because TLM interface need a dummydelay to wait for blocking transport. After subtract that, they are almost the same. After doing pipeline operation, the latency should be the same as the initiation interval(II). Take II = 1, then the total simulation time in the TLM version shoud be ((256*256*10) + (dummydelay for blocking transport)) ns.
	
