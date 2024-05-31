import hashlib
import os
import colorama

disallowed_exts = ["i64", "id0", "id1", "id2", "nam", "til", "c"]

def calculate_checksum(directory, skip_files=[]):
    sha256_hash = hashlib.sha256()
    total_files = sum([len(files) for r, d, files in os.walk(directory)])
    processed_files = 0
    for root, dirs, files in os.walk(directory):
        for file in sorted(files):
            if any(file.endswith(ext) for ext in disallowed_exts):
                processed_files += 1
                continue
            if file in skip_files:
                processed_files += 1
                continue
            file_path = os.path.join(root, file)
            with open(file_path, 'rb') as f:
                for byte_block in iter(lambda: f.read(4096), b""):
                    sha256_hash.update(hashlib.sha256(byte_block).hexdigest().encode())
            processed_files += 1
            print(f'Processed {processed_files}/{total_files} files - {file_path}', end='\r')
    old_output = f'Processed {processed_files}/{total_files} files - {file_path}'
    print(f'SHA256 Checksum: {sha256_hash.hexdigest()}' + ' ' * len(old_output) + '\n')
    return sha256_hash.hexdigest()

if __name__ == '__main__':
    try:
        if calculate_checksum('echovr/orig') == "1a9ef0b1bf3180235a4a8d5d59f4426bbb3985e98ccb80882ca0e781ce0d3c45":
            print(colorama.Fore.GREEN + 'EchoVR v34.4.631547.1 verified!\n' + colorama.Style.RESET_ALL)
        else:
            print(colorama.Fore.RED + 'EchoVR v34.4.631547.1 failed verification!\n' + colorama.Style.RESET_ALL)
    except FileNotFoundError:
        print(colorama.Fore.RED + 'EchoVR v34.4.631547.1 not found!\n' + colorama.Style.RESET_ALL)
    try:
        if calculate_checksum('echovr58/orig') == "34590aa97673ad84760607c9eb04a4aca32352d77863712889506bcd3b5dcc07":
            print(colorama.Fore.GREEN + 'EchoVR v1.58 verified!\n' + colorama.Style.RESET_ALL)
        else:
            print(colorama.Fore.RED + 'EchoVR v1.58 failed verification!\n' + colorama.Style.RESET_ALL)
    except FileNotFoundError:
        print(colorama.Fore.RED + 'EchoVR v1.58 not found!\n' + colorama.Style.RESET_ALL)