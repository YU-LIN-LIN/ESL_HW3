# Report

### GitHub repo
https://github.com/YU-LIN-LIN/ESL_HW3

### General description or introduction of the problem and your solution
	In this homework, I design a synthesizable verdion of the Gaussian blur module.
	Doing basic HLS (without optimization), and other optimized HLS offered by stratus HLS like loop-unrolling, data path optimization and pipeline.
	
### Implementation details
	timing	lat_min	lat_max	hls_config	loop_unroll	initial interval	latency	area
	20		0		3		BASIC		X			X					20		2253.6	
	20		0		3		DPA			X			X					29		1813.4	
	10		0		3		BASIC		X			X					20		2253.6	
	10		0		3		DPA			X			X					29		1813.4	
	10		0		3		DPAUA		V			X					21		2856.5	
	10		0		3		PIPELINE	X			1					1		7554.2
	10		0		3		PIPELINE	X			2					2		6457.4	
	10		0		3		PIPELINE	X			3					3		5362.1	
### Additional features of your design and models

	If the cycle time is met, set higher cycle time will not affect the HLS result.
	Optimizing with data path optimization will make area smaller, however it also increase a few latency.
	Unroll the loop will make the latency lower. The HLS result also tell us this.
	Optimizing with pipeline could decrease latency a lot, but the area will become much larger at the same time. In this homework, we can make the latency 20 times lower with just 2 times larger in area. I think it is a valuable tradeoff.

### Experimental results
	Total cycles of 'hls_config' = 'BASIC' 		: 1310719 cycles
	Total cycles of 'hls_config' = 'DPA'  		: 1900543 cycles
	Total cycles of 'hls_config' = 'DPAUA'		: 1376255 cycles
	Total cycles of 'hls_config' = 'PIPELINE' 	: 65554   cycles	(initial interval = 1)
	Total cycles of 'hls_config' = 'PIPELINE' 	: 131089  cycles	(initial interval = 2)
	Total cycles of 'hls_config' = 'PIPELINE' 	: 196624  cycles	(initial interval = 3)

### Discussions and conclusions

	In this homework, we can make the latency 20 times lower with just 2 times larger in area. I think it is a valuable tradeoff.