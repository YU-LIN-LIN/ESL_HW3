# ESL_HW3

High level synthesis of Gaussian Blur

## Compile 

### Enter the strtus directory.
  cd Gaussian_stratus/stratus

### Behavioral simulation
  make sim_B

### Verilog simulation for HLS config "BASIC".
  make sim_V_BASIC

### Verilog simulation for HLS with data path optimization.
  make sim_V_DPA
  
### Verilog simulation for HLS with data path optimization and loop unrolling.
  make sim_V_DPAUA
  
### Verilog simulation for HLS with loop pipeline.
  make sim_V_PIPELINE  
