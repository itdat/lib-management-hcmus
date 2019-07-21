
# ĐỒ ÁN MÔN HỌC: QUẢN LÝ THƯ VIỆN

## ĐỒ ÁN CUỐI KỲ

### I. Thông tin chung

&emsp;&emsp;&emsp;&emsp;Mã số bài tập:&emsp;&emsp;&emsp;&emsp;DAMH

&emsp;&emsp;&emsp;&emsp;Thời lượng dự kiến:&emsp;&emsp;&emsp;&emsp;100 - 120 tiếng

&emsp;&emsp;&emsp;&emsp;Deadline nộp bài:

&emsp;&emsp;&emsp;&emsp;Hình thức:&emsp;&emsp;&emsp;&emsp;Nhóm 2 SV

&emsp;&emsp;&emsp;&emsp;Hình thức nộp bài:&emsp;&emsp;&emsp;&emsp;Nộp qua Moodle môn học

&emsp;&emsp;&emsp;&emsp;GV phụ trách:&emsp;&emsp;&emsp;&emsp;Võ Hoài Việt

&emsp;&emsp;&emsp;&emsp;Thông tin liên lạc với GV:&emsp;&emsp;&emsp;&emsp;vhviet@fit.hcmus.edu.vn

### II. Chuẩn đầu ra cần đạt

- Thao tác được trên tập tin văn bản và nhị phân, lựa chọn được các dạng tập tin lưu trữ thích hợp.

- Xử lý được một số dạng tập tin có cấu trúc

- Áp dụng được các cấu trúc dữ liệu cơ bản ([LinkedList](https://www.stdio.vn/articles/danh-sach-lien-ket-don-106), [Stack](https://vi.wikipedia.org/wiki/Ngăn_xếp), [Queue](https://vi.wikipedia.org/wiki/Hàng_đợi))

- Áp dụng các kỹ thuật lập trình sắp xếp, tìm kiếm, [con trỏ](https://cpp.daynhauhoc.com/8/0-con-tr/), [đệ qui](https://vi.wikipedia.org/wiki/Đệ_quy)

- Sử dụng trương trình dạng Command Line

### III. Mô tả bài tập

__Đề tài quản lý thư viện__

Thư viện trường Đại học Khoa học tự nhiên TP.HCM cần viết một chương trình quản lí thư viện trên nền console và các bạn, những lập trình viên tài năng trong tương lai được chọn để thực hiện dự án này.

Thư viện cần quản lí 4 loại thông tin gồm: người dùng, độc giả, sách và các phiếu mượn/trả sách.

- Thông tin người dùng: Tên đăng nhập, mật khẩu, họ tên, ngày sinh, CMND, Địa chỉ, Giới tính, Tình trạng (activated hoặc block). Có 2 loại người dùng là quản lý thư viện và chuyên viên.

- Thông tin thẻ độc giả cần quản lí bao gồm: mã độc giả, họ tên, CMND, ngày tháng năm sinh, giới tính, email, địa chỉ, ngày lập thẻ và ngày hết hạn của thẻ (48 tháng kể từ ngày lập thẻ).

- Thông tin sách cần quản lí bao gồm: [ISBN](https://www.isbn-international.org/content/what-isbn) (mã sách), tên sách, tác giả, nhà xuất bản, năm xuất bản, thể loại, giá sách, số quyển sách.

- Mỗi phiếu mượn/trả sách chứa thông tin về mã độc giả, ngày mượn, ngày trả dự kiến, ngày trả thực tế và danh sách ISBN của các sách được mượn. Mỗi sách được mượn tối đa trong 7 ngày, nếu quá hạn sẽ bị phạt tiền 5.000 đồng/ngày. Nếu sách bị mất thì độc giả đó sẽ bị phạt số tiền tương ứng 200% giá sách.
	
#### Chức năng 1: Người dùng khi muốn sử dụng các chức năng của hệ thống phải thực hiện đăng nhập.

&emsp;&emsp;&emsp;&emsp;1.1 Đăng nhập

&emsp;&emsp;&emsp;&emsp;1.2 Đăng xuất

&emsp;&emsp;&emsp;&emsp;1.3 Thay đổi mật khẩu

&emsp;&emsp;&emsp;&emsp;1.4 Cập nhật thông tin cá nhân

&emsp;&emsp;&emsp;&emsp;1.5 Tạo người dùng

&emsp;&emsp;&emsp;&emsp;1.6 Phân quyền người dùng ( quản lý hoặc nhân viên)
	
#### Chức năng 2: Quản lý độc giả

&emsp;&emsp;&emsp;&emsp;2.1 Xem danh sách độc giả trong thư viện

&emsp;&emsp;&emsp;&emsp;2.2 Thêm độc giả

&emsp;&emsp;&emsp;&emsp;2.3 Chỉnh sửa thông tin một độc giả

&emsp;&emsp;&emsp;&emsp;2.4 Xóa thông tin một độc giả

&emsp;&emsp;&emsp;&emsp;2.5 Tìm kiếm độc giả theo CMND

&emsp;&emsp;&emsp;&emsp;2.6 Tìm kiếm sách theo họ tên
		
#### Chức năng 3: Quản lý sách
	
&emsp;&emsp;&emsp;&emsp;3.1 Xem danh sách các sách trong thư viện

&emsp;&emsp;&emsp;&emsp;3.2 Thêm sách

&emsp;&emsp;&emsp;&emsp;3.3 Chỉnh sửa thông tin một quyển sách

&emsp;&emsp;&emsp;&emsp;3.4 Xóa thông tin sách

&emsp;&emsp;&emsp;&emsp;3.5 Tìm kiếm sách theo ISBN

&emsp;&emsp;&emsp;&emsp;3.6 Tìm kiếm sách theo tên sách
		
#### Chức năng 4: Lập phiếu mượn sách
	
#### Chức năng 5: Lập phiếu trả sách
	
#### Chức năng 6: Các thống kê cơ bản

&emsp;&emsp;&emsp;&emsp;6.1 Thống kê số lượng sách trong thư viện

&emsp;&emsp;&emsp;&emsp;6.2 Thống kê số lượng sách theo thể loại

&emsp;&emsp;&emsp;&emsp;6.3 Thống kê số lượng độc giả

&emsp;&emsp;&emsp;&emsp;6.4 Thống kê số lượng độc giả theo giới tính

&emsp;&emsp;&emsp;&emsp;6.5 Thống kê số sách đang được mượn

&emsp;&emsp;&emsp;&emsp;6.6 Thống kê danh sách độc giả bị trễ hạn

<table width="100%">
	<thead>
		<tr>
			<th colspan ="2">Bảng phân quyền thực hiện chức năng</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>Admin hệ thống</td>
			<td>Tât các các chức năng (chỉ có một user admin)</td>
		</tr>
	<tr>
		<td rowspan="6">Quản lý</td>
		<td>1.1, 1.2, 1.3, 1.4</td>
	</tr>
	<tr>
		<td>2.xxx</td>
	</tr>
	<tr>
		<td>3.xxx</td>
	</tr>
	<tr>
		<td>4.xxx</td>
	</tr>
	<tr>
		<td>5.xxx</td>
	</tr>
	<tr>
		<td>6.xxx</td>
	</tr>
		<tr>
		<td rowspan="6">Chuyên viên</td>
		<td>1.1, 1.2, 1.3, 1.4</td>
	</tr>
	<tr>
		<td>2.1, 2.2, 2.3, 2.5, 2.6</td>
	</tr>
	<tr>
		<td>3.5, 3.6</td>
	</tr>
	<tr>
		<td>4.xxx</td>
	</tr>
	<tr>
		<td>5.xxx</td>
	</tr>
	<tr>
		<td>6.5, 6.6</td>
	</tr>
	</tbody>
</table>

#### Ghi chú:

- Viết chương trình dạng command line.

- Sinh viên tự thiết kế cấu trúc dữ liệu và cấu trúc lưu trữ thích hợp.

- Đối với các chức năng tìm kiếm sinh viên lưu ý áp dụng các kiến thực đã học trên lớp để việc thực hiện tìm kiếm là nhanh nhất có thể.

- Sinh viên có thể đề xuất thêm thuộc tính thông tin quản lý và chức năng để chương trình của mình trở nên tiện dụng.

### IV. Các yêu cầu & quy định chi tiết cho bài nộp

- Bài nộp được nén .RAR hoặc .ZIP và được nộp trên moodle. Với cấu trúc tên tập tin theo thứ tự mã số sinh viên SV1_SV2.RAR hoặc SV1_SV2.ZIP ( Ví dụ: 0912496_0912407.RAR)

- Cấu trúc thư mục nộp bài gồm như sau:

	- Documents: chứa báo cáo đồ án, bảng phân công thành viên và hướng dẫn sử dụng

	- Release: chứa tập tin exe và các dữ liệu cần thiết để chạy chương trình.

	- Program: file thực thi và mã nguồn chương trình

	- Demo: chứa video demo các chức năng của chương trình.

### V. Hướng dẫn chi tiết

Sinh viên tự nghiên cứu.

### VI. Các đánh giá

|STT |Tên kết quả                       |Tỉ lệ điểm |Ghi chú                                                                                                           |
|----|----------------------------------|-----------|------------------------------------------------------------------------------------------------------------------|
|1   |Mã nguồn                          |60%        |Cung cấp các thư viện và mã nguồn đầy đủ để biên dịch.                                                            |
|2   |Phong cách lập trình              |20%        |Cấu trúc chương trình rõ ràng, hàm/biến đặt tên dễ hiểu và gợi nhớ và tuân thủ các qui tắc lập trình.             |
|3   |Báo cáo, demo và hướng dẫn sử dụng|20%        |Báo cáo các chức năng của chương trình, hướng dẫn sử dụng cho người dùng, video minh họa từng bước và dữ liệu test|

### VII. Tài liệu tham khảo

Slide bài giảng lý thuyết

### VIII. Các quy định khác

- Chương trình phải có hướng dẫn sử dụng (Không có hướng dẫn sử dụng sẽ bị trừ 50% số điểm của phần phần chương trình).

- Tất cả các bài làm sai quy định đều bị 0 điểm cho mỗi bài.

- Hai bài giống nhau từ 80% trở lên sẽ bị 0 điểm cho cả hai bất kể ai là tác giả.

- Các trường hợp sử dụng mã nguồn không ghi rõ nguồn tham khảo sẽ bị điểm 0 cho tất các các bài và các tác giả).

- Các bài làm xuất sắc sẽ được điểm cộng.

- Không nhận bài nộp trễ qua mail.
