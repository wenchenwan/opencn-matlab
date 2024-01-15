import re

# Function to clean G93 and G94 commands and F values within G93/G94 blocks
def clean_commands(input_filename, output_filename):
    with open(input_filename, 'r') as f:
        lines = f.readlines()

    result = []

    # Regular expression to find G93/G94 blocks
    pattern = re.compile(r'G9[3-4]+')
    in_g93_block = False  # Indicates if we are inside a G93/G94 block

    for line in lines:
        if 'G93' in line:
            in_g93_block = True
            line = re.sub(pattern, '', line)  # Remove G93/G94 commands
        elif 'G94' in line:
            if in_g93_block:
                line = re.sub(pattern, '', line)  # Remove G93/G94 commands
            in_g93_block = False

        if in_g93_block and 'F' in line:
            line = re.sub(r'F[0-9.]+', '', line)  # Remove the F value
        result.append(line.strip())  # Add the cleaned line to the result

    with open(output_filename, 'w') as f:
        f.write('\n'.join(result))

# Specify the input and output file names
input_file = 'ngc_test/misc/036_dome_finition_PostProHGS_10Line_v1.ngc'  # Replace with your input file name
output_file = 'ngc_test/misc/036_dome_finition_PostProHGS_10Line_v1_without_G93.ngc'  # Replace with your output file name

# Call the function to clean the commands
clean_commands(input_file, output_file)
print(f"Commands have been cleaned and saved to {output_file}.")
