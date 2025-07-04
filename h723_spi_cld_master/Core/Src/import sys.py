import os
import shutil

# กำหนดเส้นทางไปยัง Desktop
desktop_path = os.path.join(os.path.expanduser("~"), "Desktop")

# สร้างโฟลเดอร์ตามประเภทของไฟล์
folders = {
    "Images": [".jpg", ".jpeg", ".png", ".gif", ".bmp", ".tiff"],
    "Documents": [".txt", ".pdf", ".docx", ".xlsx", ".pptx"],
    "Videos": [".mp4", ".avi", ".mov", ".mkv"],
    "Music": [".mp3", ".wav", ".aac", ".flac"],
    "Others": []
}

# สร้างโฟลเดอร์หากยังไม่มี
for folder in folders.keys():
    folder_path = os.path.join(desktop_path, folder)
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)

# ย้ายไฟล์ตามประเภทไปยังโฟลเดอร์ที่ตรงกัน
for file_name in os.listdir(desktop_path):
    file_path = os.path.join(desktop_path, file_name)
    if os.path.isfile(file_path):
        moved = False
        for folder, extensions in folders.items():
            if any(file_name.lower().endswith(ext) for ext in extensions):
                shutil.move(file_path, os.path.join(desktop_path, folder, file_name))
                moved = True
                break
        if not moved:
            shutil.move(file_path, os.path.join(desktop_path, "Others", file_name))

print("จัดระเบียบไฟล์ใน Desktop เรียบร้อยแล้ว")
