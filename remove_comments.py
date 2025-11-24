import os
import re

def remove_comments_from_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        lines = content.split('\n')
        new_lines = []
        
        for line in lines:
            if '//' in line:
                comment_pos = line.find('//')
                code_part = line[:comment_pos].rstrip()
                if code_part:
                    new_lines.append(code_part)
                else:
                    new_lines.append('')
            else:
                new_lines.append(line)
        
        new_content = '\n'.join(new_lines)
        
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(new_content)
        
        return True
    except Exception as e:
        print(f"Error processing {filepath}: {e}")
        return False

def process_directory(directory):
    extensions = ['.cpp', '.h', '.cs']
    processed = 0
    
    for root, dirs, files in os.walk(directory):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                filepath = os.path.join(root, file)
                if remove_comments_from_file(filepath):
                    processed += 1
                    print(f"Processed: {filepath}")
    
    print(f"Total files processed: {processed}")

if __name__ == '__main__':
    process_directory('AVA-2025')

