# ĐỒ ÁN MÔN HỌC: QUẢN LÝ THƯ VIỆN

## ĐỒ ÁN CUỐI KỲ

### I. Thông tin chung

	Mã số bài tập:				DAMH

	Thời lượng dự kiến:			100 - 120 tiếng

	Deadline nộp bài:

	Hình thức:				Nhóm 2 SV

	Hình thức nộp bài:			Nộp qua Moodle môn học

	GV phụ trách:				Võ Hoài Việt

	Thông tin liên lạc với GV:		vhviet@fit.hcmus.edu.vn

### II. Chuẩn đầu ra cần đạt

	- Thao tác được trên tập tin văn bản và nhị phân, lựa chọn được các dạng tập tin lưu trữ thích hợp.

	- Xử lý được một số dạng tập tin có cấu trúc

	- Áp dụng được các cấu trúc dữ liệu cơ bản (LinkedList, Stack, Queue)

	- Áp dụng các kỹ thuật lập trình sắp xếp, tìm kiếm, con trỏ, đệ qui

	- Sử dụng trương trình dạng Command Line

### III. Mô tả bài tập

	__ Đề tài quản lý thư viện __

	Thư viện trường Đại học Khoa học tự nhiên TP.HCM cần viết một chương trình quản lí thư viện trên nền console và các bạn, những lập trình viên tài năng trong tương lai được chọn để thực hiện dự án này.

	Thư viện cần quản lí 4 loại thông tin gồm: người dùng, độc giả, sách và các phiếu mượn/trả sách.

		- Thông tin người dùng: Tên đăng nhập, mật khẩu, họ tên, ngày sinh, CMND, Địa chỉ, Giới tính, Tình trạng (activated hoặc block). Có 2 loại người dùng là quản lý thư viện và chuyên viên.

		- Thông tin thẻ độc giả cần quản lí bao gồm: mã độc giả, họ tên, CMND, ngày tháng năm sinh, giới tính, email, địa chỉ, ngày lập thẻ và ngày hết hạn của thẻ (48 tháng kể từ ngày lập thẻ).

		- Thông tin sách cần quản lí bao gồm: ISBN (mã sách), tên sách, tác giả, nhà xuất bản, năm xuất bản, thể loại, giá sách, số quyển sách.

		- Mỗi phiếu mượn/trả sách chứa thông tin về mã độc giả, ngày mượn, ngày trả dự kiến, ngày trả thực tế và danh sách ISBN của các sách được mượn. Mỗi sách được mượn tối đa trong 7 ngày, nếu quá hạn sẽ bị phạt tiền 5.000 đồng/ngày. Nếu sách bị mất thì độc giả đó sẽ bị phạt số tiền tương ứng 200% giá sách.
	
	#### Chức năng 1: Người dùng khi muốn sử dụng các chức năng của hệ thống phải thực hiện đăng nhập.

		1.1 Đăng nhập
		
		1.2 Đăng xuất
		
		1.3 Thay đổi mật khẩu
		
		1.4 Cập nhật thông tin cá nhân
		
		1.5 Tạo người dùng
		
		1.6 Phân quyền người dùng ( quản lý hoặc nhân viên)
	
	#### Chức năng 2: Quản lý độc giả
	
		2.1 Xem danh sách độc giả trong thư viện

		2.2 Thêm độc giả

		2.3 Chỉnh sửa thông tin một độc giả

		2.4 Xóa thông tin một độc giả

		2.5 Tìm kiếm độc giả theo CMND

		2.6 Tìm kiếm sách theo họ tên
		
	#### Chức năng 3: Quản lý sách
	
		3.1 Xem danh sách các sách trong thư viện

		3.2 Thêm sách

		3.3 Chỉnh sửa thông tin một quyển sách

		3.4 Xóa thông tin sách

		3.5 Tìm kiếm sách theo ISBN

		3.6 Tìm kiếm sách theo tên sách
		
	#### Chức năng 4: Lập phiếu mượn sách
	
	#### Chức năng 5: Lập phiếu trả sách
	
	#### Chức năng 6: Các thống kê cơ bản
	
		6.1 Thống kê số lượng sách trong thư viện

		6.2 Thống kê số lượng sách theo thể loại

		6.3 Thống kê số lượng độc giả

		6.4 Thống kê số lượng độc giả theo giới tính

		6.5 Thống kê số sách đang được mượn

		6.6 Thống kê danh sách độc giả bị trễ hạn
		
	Bảng phân quyền thực hiện chức năng
	--------------------------|----------------------------------
	Admin hệ thống | Tất cả các chức năng (chỉ có một user admin)
