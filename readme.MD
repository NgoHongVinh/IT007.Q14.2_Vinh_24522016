# 📘 Hướng Dẫn Sử Dụng Repository

## Script biên dịch – `compile.sh`
Sinh viên đã xóa toàn bộ các tệp `.o` cũ.  
Để biên dịch lại toàn bộ chương trình, vui lòng sử dụng lệnh:

```bash
bash compile.sh
```

Script này sẽ tự động biên dịch **tất cả các tệp `.c`** trong thư mục và tạo ra các tệp thực thi (`.o`) ở cùng cấp thư mục.  
Sau khi biên dịch xong, có thể chạy trực tiếp chương trình bằng lệnh:

```bash
./<tên_file_thực_thi>
```

---

## Bài 1 – Thực hành tiến trình và bộ nhớ chia sẻ
Các tệp cần thực thi lần lượt là:
- `test_fork.c`
- `test_exec1.c`
- `test_system.c`
- `test_shm_A.c`
- `test_shm_B.c`

**Lưu ý:**
- Hai ví dụ đầu (`test_exec1.c`, `test_system.c`) sử dụng script `count.sh`, kết quả đầu ra được lưu vào tệp `count.txt`.
- Đối với phần **bộ nhớ chia sẻ** (`test_shm_A.c` và `test_shm_B.c`):
  - Cần mở **hai cửa sổ WSL riêng biệt**.
  - Thực thi **A trước**, sau đó chuyển sang cửa sổ còn lại để thực thi **B**.

---

## Bài 2 – Đo thời gian thực thi lệnh
- Tệp cần thực thi: **`time.c`**  
- Chương trình dùng để đo thời gian chạy của một lệnh shell bất kỳ thông qua cơ chế `fork()`, `execvp()` và `gettimeofday()`.

---

## Bài 3 – Xử lý tín hiệu và tiến trình con
- Tệp cần thực thi: **`stop.c`**  
- Chương trình khởi chạy script `count.sh` và xử lý tín hiệu `SIGINT` (Ctrl + C) để dừng tiến trình con và in ra thông báo.

---

## Bài 4 
- Tệp cần thực thi: **`producer_consumer.c`**  
- Tiến trình cha đóng vai trò **Producer** tạo số ngẫu nhiên (10–20) và ghi vào buffer 10 bytes trong shared memory.  
- Tiến trình con **Consumer** đọc các giá trị này, in ra màn hình và cộng dồn tổng.  
- Khi tổng vượt quá 100, cả hai tiến trình dừng lại.

---

## Video minh họa
Thư mục **`/video`** chứa kết quả demo của bốn bài thực hành.

---

### 🩺 Ghi chú
> Sinh viên xin phép **vắng buổi học ngày 27/10/2025** do lý do sức khỏe (Ốm).
