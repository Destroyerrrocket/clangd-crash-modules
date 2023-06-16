#!/usr/bin/env python3
import json
import subprocess

def main():
	p = subprocess.Popen(["ninja -t compdb"], stdout=subprocess.PIPE, shell=True)
	(output, err) = p.communicate()
	jsondata = json.loads(output.decode('utf-8'))
	datafilter = filter(lambda entry: entry['output'].endswith(".o"), jsondata)
	json.dump(list(datafilter), open('compile_commands.json', 'w'), indent=4)

if __name__ == '__main__':
	main()
