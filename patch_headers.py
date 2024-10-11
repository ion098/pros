'''
Adds __atrribute__((pcs("aapcs")) to all sdk function declarations to allow properly linking
with the sdk (which uses the soft float abi) when building pros with the hard float abi
'''

from os import listdir
from os.path import isfile, join

include_path = "./firmware/libv5rts/sdk/vexv5/include/"
patched_include_path = "./firmware/libv5rts/sdk/vexv5/patched_include/"
files = [f for f in listdir(include_path) if isfile(join(include_path, f)) and str(f).endswith(".h")]

for file_name in files:
    header_file = ""
    output = ""
    skip_next_line = False
    with open(join(include_path, file_name), "r") as file:
        header_file = file.read()
    for line in header_file.splitlines():
        if skip_next_line:
            # This line is a macro continuation
            if not line.endswith(("\\")):
                # maco continuation ends here
                skip_next_line = False
            continue
        if line.strip().startswith(("/", "*")):
            # it's a comment
            output += f"{line}\n"
            continue
        if line.strip().startswith(("#")):
            # it's a preprocessor directive
            output += f"{line}\n"
            if line.endswith(("\\")):
                skip_next_line = True
            continue
        if line.strip().startswith(("}", "{", "extern")):
            # it's an extern c block or struct definition
            output += f"{line}\n"
            continue
        if line.strip().startswith(("typedef", "struct", "enum")):
            # it's a struct/enum definition or typedef
            output += f"{line}\n"
            continue
        if not line or line.isspace():
            # it's blank
            output += f"{line}\n"
            continue
        if ");" not in line:
            # just in case something that isn't a function slips past the previous checks
            # ");" should only occur in a function definition
            output += f"{line}\n"
            continue
        output += f"__attribute__((pcs(\"aapcs\"))) {line}\n"
    with open(join(patched_include_path, file_name), "w") as file:
        file.write(output)
