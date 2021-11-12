#!/bin/bash

CLANG_FORMAT_VERSION="13"


function print_usage () {
    echo "Usage:"
    echo "    $0"
    echo "   --workplace                        Workplace where to apply formater"
    echo "   --fallback                         Fallback style format to be use: By default is Google"
    echo "   --clangsetup                       <true|false> If true, install clang format. Default is false"
    echo "   --apply                            <true|false> If true, format the code. Default is false"
    echo "   --help                             Print this page"
    echo
}

function log_() {
    echo "[$(basename "$0")] $*"
}


function install_clang(){
    log_ "Installing clang-format-$CLANG_FORMAT_VERSION"    
    apt-get update && apt-get install -y --no-install-recommends clang-format-"$CLANG_FORMAT_VERSION"
}


function clang_file() {
	
    log_ "Run running clang on ${1}"
    
    local files=$(find . -regex '.*\.\(cpp\|hpp\|h\|cc\|cxx\)'  | tr '\n' ' ') 

    
    /usr/bin/clang-format-${CLANG_FORMAT_VERSION} ${3} --style=file --fallback-style=${2} ${files} || local format_status=$?
		
	if [[ "${format_status}" -ne 0 ]]; then
		log_ "Run clang-format your code before commit"
	fi
	
	return ${format_status} 
	
}


# Returns 0 (success) if no error occurs, 1 otherwise.
function parse_opts () {
    # Parse options
    local opt
    while [[ $# -gt 0 ]]; do
    opt="$1"

    case $opt in
        --workplace)
        workplace_path="$2"; shift
        ;;
        -h|--help)
        print_usage; exit 0;
        ;;
        --fallback)
        fallback_style="${2}"; shift
        ;;
        --clangsetup)
        flag_clang="$2"; shift
        ;;
        --apply)
        flag_apply="$2"; shift
        ;;
        *)
        log_ "Unrecognized option '$opt'."; exit 1
        ;;
    esac
    shift
    done
}

parse_opts ${@}


# If the path is not defined, default to the current
workplace_path="${workplace_path:-.}"

# If the fallback style is not defined, default to Google
fallback_style="${fallback_style:-Google}"

# If the install flag is not set, default to false
flag_clang="${flag_clang:-false}"

# If the apply flag is not set, default to false
flag_apply="${flag_apply:-false}"

log_ "workplace_path: ${workplace_path}"
log_ "fallback_style: ${fallback_style}"
log_ "flag install clang: ${flag_clang}"
log_ "flag apply format: ${flag_apply}"


cd ${workplace_path}

if [[ ${flag_clang} == "true" ]]; then
    log_ "Clang install"
    install_clang
fi

if [[ ${flag_apply} == "true" ]]; then
    opt="-i --verbose"
    clang_file ${workplace_path} ${fallback_style} "${opt}" || exit_code=$?
else
    opt="-n --Werror"
    clang_file ${workplace_path} ${fallback_style} "${opt}" || exit_code=$?
fi

log_ "Job Completed"

exit $exit_code
