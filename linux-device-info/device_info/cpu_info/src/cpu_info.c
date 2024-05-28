#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * *-cpu
          description: CPU
          product: Intel(R) Core(TM) i7-10700 CPU @ 2.90GHz
          vendor: Intel Corp.
          physical id: 45
          bus info: cpu@0
          version: 6.165.5
          serial: To Be Filled By O.E.M.
          slot: U3E1
          size: 4694MHz
          capacity: 4800MHz
          width: 64 bits
          clock: 100MHz
          capabilities: lm fpu fpu_exception wp vme de pse tsc msr pae mce cx8 apic
          sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm
          pbe syscall nx pdpe1gb rdtscp x86-64 constant_tsc art arch_perfmon pebs bts
          rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor
          ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic
          movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm
          3dnowprefetch cpuid_fault epb invpcid_single ssbd ibrs ibpb stibp ibrs_enhanced
          tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2
          erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves
          dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp pku ospke md_clear flush_l1d
          arch_capabilities cpufreq
          configuration: cores=8 enabledcores=8 microcode=248 threads=16
 *
 *
 *
 */

#define MAX_LINE_LENGTH 256

struct cpu_info
{

char cpu_name[MAX_LINE_LENGTH];
uint8_t no_cores;
uint8_t no_threads;
uint32_t qualified_speed;
uint32_t max_turbo_boost_speed;

};


int get_cpu_info(struct cpu_info *c_info);


int main() {
	struct cpu_info c_info;

	get_cpu_info(&c_info);

    // Print CPU information
    printf("CPU Name: %s\n", c_info.cpu_name);
    printf("Number of Cores: %d\n", c_info.no_cores);
    printf("Number of Threads: %d\n", c_info.no_threads);
    printf("Max Qualified Speed: %ld MHz\n", c_info.qualified_speed);
    printf("Max Turbo Boost Speed: %ld MHz\n", c_info.qualified_speed);

    return 0;
}


int get_cpu_info(struct cpu_info *c_info)
{
	// Open the CPU info file
	    FILE* cpuinfo_file = fopen("/proc/cpuinfo", "r");
	    if (cpuinfo_file == NULL) {
	        perror("Error opening CPU info file");
	        return 1;
	    }


	    // Read lines from the CPU info file
	    char line[MAX_LINE_LENGTH];
	    while (fgets(line, MAX_LINE_LENGTH, cpuinfo_file) != NULL) {
	        // Check for CPU model name
	        if (strstr(line, "model name") != NULL) {
	            sscanf(line, "model name\t: %[^\n]", c_info->cpu_name);
	        }
	        // Check for number of cores
	        else if (strstr(line, "cpu cores") != NULL) {
	            sscanf(line, "cpu cores\t: %d", &c_info->no_cores);
	        }
	        // Check for number of threads
	        else if (strstr(line, "siblings") != NULL) {
	            sscanf(line, "siblings\t: %d", &c_info->no_threads);
	        }
	        // Check for max speed
	        else if (strstr(line, "cpu MHz") != NULL) {
	            sscanf(line, "cpu MHz\t: %ld", &c_info->qualified_speed);
	        }
	        // Check for max turbo speed (if available)
	        else if (strstr(line, "cpu MHz") != NULL) {
	            sscanf(line, "cpu MHz\t: %ld", &c_info->max_turbo_boost_speed);
	        }
	    }

	    // Close the CPU info file
	    fclose(cpuinfo_file);

}


