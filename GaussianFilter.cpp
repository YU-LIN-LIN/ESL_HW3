#include <cmath>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif

#include "GaussianFilter.h"
#include "directives.h"

GaussianFilter::GaussianFilter( sc_module_name n ): sc_module( n )
{
#ifndef NATIVE_SYSTEMC
	HLS_FLATTEN_ARRAY(val);
#endif
	SC_THREAD( do_filter );
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);
        
#ifndef NATIVE_SYSTEMC
	i_rgb.clk_rst(i_clk, i_rst);
  o_result.clk_rst(i_clk, i_rst);
#endif
}

GaussianFilter::~GaussianFilter() {}

// sobel mask
// const int mask[MASK_N][MASK_X][MASK_Y] = {{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}},

//                                     {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}};

// gaussian mask
const int mask[MASK_X][MASK_Y] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};


void GaussianFilter::do_filter() {
	

	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_rgb.reset();
		o_result.reset();
#endif
		wait();
	}
	

	while (true) {
		// Add a HLS_PIPELINE_LOOP directive that is enabled when II is set.
		#if defined (I)
			HLS_PIPELINE_LOOP(SOFT_STALL, I, "Loop" );
		#endif
		// HLS_PIPELINE_LOOP(SOFT_STALL, 2, "Loop" );
		
		// for (unsigned int i = 0; i<MASK_N; ++i) {
		// 	HLS_CONSTRAIN_LATENCY(0, 1, "lat00");
		// 	val[i] = 0;
		// }
		sc_dt::sc_uint<24> total;
		sc_dt::sc_uint<24> total_r, total_g, total_b;
		total = 0;
		total_r = 0;
		total_g = 0;
		total_b = 0;

		for (unsigned int v = 0; v<MASK_Y; ++v) {
			COL_LOOP;
			for (unsigned int u = 0; u<MASK_X; ++u) {
				ROW_LOOP;
				sc_dt::sc_uint<24> rgb;
#ifndef NATIVE_SYSTEMC
				{
					HLS_DEFINE_PROTOCOL("input");
					rgb = i_rgb.get();
					wait();
				}
#else
				rgb = i_rgb.read();
#endif
				// unsigned char grey = (rgb.range(7,0) + rgb.range(15,8) + rgb.range(23, 16))/3;
				// for (unsigned int i = 0; i != MASK_N; ++i) {
				// 	HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
				// 	val[i] += grey * mask[i][u][v];
				// }

				HLS_CONSTRAIN_LATENCY(0, 3, "lat01");
				total_r += rgb.range(7, 0) * mask[u][v];
				total_g += rgb.range(15, 8) * mask[u][v];
				total_b += rgb.range(23, 16) * mask[u][v];

			}
		}
		// for (unsigned int i = 0; i != MASK_N; ++i) {
		// 	HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
		// 	total += val[i] * val[i];
		// }
		total.range(7, 0) = total_r / 16;
		total.range(15, 8) = total_g / 16;
		total.range(23, 16) = total_b / 16;

#ifndef NATIVE_SYSTEMC
		{
			HLS_DEFINE_PROTOCOL("output");
			o_result.put(total);
			wait();
		}
#else
		o_result.write(total);
#endif
	}
}
