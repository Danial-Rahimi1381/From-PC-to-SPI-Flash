################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Sources/%.obj: ../Sources/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/RayFan/workspace_v12/From PC to SPI-Flash" --include_path="C:/Users/RayFan/workspace_v12/From PC to SPI-Flash/include" --include_path="C:/Users/RayFan/workspace_v12/header_files/common/include" --include_path="C:/Users/RayFan/workspace_v12/header_files/headers/include" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Sources/$(basename $(<F)).d_raw" --obj_directory="Sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Sources/%.obj: ../Sources/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/RayFan/workspace_v12/From PC to SPI-Flash" --include_path="C:/Users/RayFan/workspace_v12/From PC to SPI-Flash/include" --include_path="C:/Users/RayFan/workspace_v12/header_files/common/include" --include_path="C:/Users/RayFan/workspace_v12/header_files/headers/include" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Sources/$(basename $(<F)).d_raw" --obj_directory="Sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


