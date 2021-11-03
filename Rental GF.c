/*************************************************
 HEADER DAN MACRO
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#define key 69
#define MAX_STAFF 25
#define MAX_PEMESANAN_PER_STAFF 100
#define MAX_PEMESANAN_PER_CUSTOMER 100
#define tarif_awal 50000

/*************************************************
 STRUKTUR DATA
*************************************************/

struct data_staff
{
    int staff_num;
    char nama[25];
    char username[25];
    char pass[10];
    char email[25];
    char nomor[15];
    char tgl_lahir[10];
    int umur;
    int rating;
    int elo;
    char status[10];
    int tarif;
};

struct data_customer
{
    int customer_num;
    char nama[25];
    char username[25];
    char pass[10];
    char email[25];
    char nomor[15];
    char tgl_lahir[10];
    int umur;
};

struct data_pemesanan
{
    int kode_pemesanan;
    char nama_customer[25];
    char nama_staff[25];
    char tgl_pertemuan[10];
    int durasi;
    char status[10];
};

struct data_rental
{
    int jumlah_customer;
    int jumlah_staff;
    int jumlah_pemesanan;
    struct data_staff staff[100];
    struct data_customer customer[100];
    struct data_pemesanan pesanan[100];
};

typedef struct data_staff staff;
typedef struct data_customer customer;
typedef struct data_pemesanan pesanan;
typedef struct data_rental rental;

/*************************************************
 FUNGSI LAIN-LAIN
*************************************************/

void config()
{
    system("title \"GF RENTAL\"");
    system("color 1f");
}

void clrscr()
{
    system("cls");
}

void inisialisasi_struct(rental *data)
{
    data->jumlah_staff = 0;
    data->jumlah_customer = 0;
    data->jumlah_pemesanan = 0;
    return;
}

void header()
{
    printf(" ============================================\n");
    printf(" =          WELCOME  TO  \"GF RENTAL\"        =\n");
    printf(" ============================================\n\n\n");
}

void disclaimer()
{
	char cek;
	do
    {
        clrscr();
        header();
        printf(" ===== TERMS & CONDITIONS =====\n\n");
        printf(" Pengguna program GF Rental wajib membaca dan mengikuti ketentuan-ketentuan berikut:\n");
        printf(" 1.  Staff di GF Rental merupakan teman wanita yang akan di \"sewa\" atau dipesan oleh customer ");
        printf(" 2.  Kuasa admin absolut dan tidak bisa diganggu-gugat kecuali oleh sesama admin");
        printf(" 3.  Customer dilarang keras melakukan pelecehan seksual dengan cara apapun terhadap teman wanita yang disewa (Akan ada hukuman pidana yang diberlakukan)\n");
        printf(" 4.  Customer diberikan waktu maksimal 2x24 jam untuk menyewa teman wanitanya dan tidak boleh menyewa lebih dari 1 teman wanita (Melanggar nomor 2 dikenakan denda sebesar Rp 2.500.000,00 +  kecuali ada perjanjian)\n");
        printf(" 5.  Customer dapat melakukan pembayaran di awal atau diberikan batas pembayaran maksimal 2x24 jam setelah penyewaan (Terlambat melakukan pembayaran dikenakan denda sebesar 10% per hari)\n");
        printf(" 6.  Customer dapat memperpanjang lama penyewaan dengan maksimal lama penyewaan 2x24 jam\n");
        printf(" 7.  Customer memiliki hak untuk menambah rating dari setiap teman wanita yang disewanya\n");
        printf(" 8.  Staff memiliki wewenang untuk memantau pergerakan dari para customer dan bekerja sama dengan kepolisian\n");
        printf(" 9.  Staff dan admin tidak berhak mencampuri urusan customer selama tidak melanggar peraturan dan ketentuan yang ada\n");
        printf(" 10. Staff diwajibkan selalu berkoordinasi dengan admin\n");
        printf(" 11. Transaksi penyewaan tidak boleh dibatalkan oleh customer kecuali ada perjanjian dan uang yang sudah terbayar tidak dapat dikembalikan\n");
        printf(" 12. Staff berhak untuk membatalkan pertemuan jika customer tidak hadir di tempat pertemuan yang telah ditentukan selama lebih dari 1 jam");
        printf(" 13. Melanggar segala ketentuan di atas akan diancam pemecatan untuk staff dan \"blacklist\" untuk customer\n");
        printf(" 14. Staff ataupun customer yang telah menerima terms & condition ini kehilangan haknya untuk menuntut pihak GF Rental bilamana terjadi masalah dengan hal-hal yang menyangkut aplikasi GF Rental\n");
        printf(" ==============================\n\n");
        printf(" | Tekan V untuk menyetujui dan melanjutkan atau tekan X untuk kembali ke menu utama | ");
        cek = getch();
        cek = toupper(cek);
	}
	while(cek != 'V' && cek != 'X');
	if(cek == 'V')
        return;
    else
        main();
}

void protect_pass(char *pass, int status)
{
    int i, j;
    for(i = 0; i < strlen(pass); i++)
    {
        if(status == 0)
            pass[i] = pass[i] + key;
        if(status == 1)
            pass[i] = pass[i] - key;
    }
}

int is_num(char cek_karakter)
{
	if(cek_karakter<'0' || cek_karakter>'9') return 0;
	return 1;
}

int cek_format_nomor_telepon(char *telp, int l)
{
    int i;
    for(i = 0; i < l; i++)
    {
        if(!is_num(telp[i]))
            return 0;
    }
    return 1;
}

int cek_format_tanggal(char *tanggal)
{
	if(!is_num(tanggal[0]) || !is_num(tanggal[1]) || tanggal[2]!='/' || !is_num(tanggal[3]) || !is_num(tanggal[4]) || tanggal[5]!='/' || !is_num(tanggal[6]) || !is_num(tanggal[7]) || !is_num(tanggal[8]) || !is_num(tanggal[9])) return 0;
	if(tanggal[0]>'3') return 0;
	if(tanggal[0]=='3' && tanggal[1]>'1') return 0;
	if(tanggal[0]=='0' && tanggal[1]=='0') return 0;
	if(tanggal[3]>'1') return 0;
	if(tanggal[3]=='1' && tanggal[4]>'2') return 0;
	if(tanggal[3]=='0' && tanggal[4]=='0') return 0;
	if(tanggal[3]=='0' && tanggal[4]=='2')
    {
		if(tanggal[0]=='3') return 0;
		if(tanggal[0]=='2' && tanggal[1]=='9')
		{
			if( ( (tanggal[8]-'0')*10 + (tanggal[9]-'0') ) % 4 != 0 ) return 0;
		}
	}
	else
	{
		if(tanggal[4]<'7' && (tanggal[4]-'0')%2==0)
		{
			if(tanggal[0]=='3' && tanggal[1]=='1') return 0;
		}
		else
		{
			if(tanggal[4]=='9' || tanggal[4]=='1')
			{
				if(tanggal[0]=='3' && tanggal[1]=='1') return 0;
			}
		}
	}
	return 1;
}

void generate_number(int *num, int a, int b)
{
    srand(time(NULL));
    *num = rand() % b + a;
    return;
}

void ubah_spasi(char *arr)
{
    int i;
    for(i = 0; i < strlen(arr); i++)
    {
        if(arr[i] == '_')
            arr[i] = ' ';
        else if(arr[i] == ' ')
            arr[i] = '_';
    }
    return;
}

void hitung_tarif(int *tarif, int *poin)
{
    *tarif = tarif_awal * ((float) *poin/1000);
    return;
}

void rate_staff(rental *data, int rating, int idx)
{
    if(data->staff[idx].rating == 0)
        data->staff[idx].rating = rating;
    else
    {
        data->staff[idx].rating += rating;
        data->staff[idx].rating /= 2;
    }
    if(rating >= 3)
        data->staff[idx].elo += 500;
    else
        data->staff[idx].elo -= 250;
    simpan_data_staff(data);
    return;
}

void konfirmasi_rental(rental *data, int idx)
{
    int i;
	int jam, total, nomor, idx_staff;
	int flag = 0;
	char pilih;
	char tgl[10];
	char crd[10];
	do
    {
        printf("\n Masukkan nomor dari staff yang ingin kamu pilih : ");
        scanf("%d",&nomor);
        for(i = 0; i < data->jumlah_staff; i++)
        {
            if(data->staff[i].staff_num == nomor)
            {
                flag = 1;
                idx_staff = i;
            }
        }
    }
    while(flag == 0);
	do
	{
        printf(" Berapa lama kamu ingin ditemani (jam) [min 1 jam, maks 48 jam]? ");
        scanf("%d", &jam);
        do
        {
            printf(" Pada tanggal berapa [DD/MM/YYYY]? ");
            scanf("%s", tgl);
        }
        while(cek_format_tanggal(tgl) == 0);
	}
	while(jam < 1 && jam > 48);
	total = data->staff[idx_staff].tarif * jam;
	printf(" Harga yang harus kamu bayar : %d\n", total);
	do
    {
        printf("\n Apakah kamu bersedia [Y/N]? ");
        fflush(stdin);
        scanf("%c", &pilih);
        pilih = toupper(pilih);
    }
    while(pilih != 'Y' && pilih != 'N');
	if(pilih == 'Y')
	{
	    generate_number(&data->pesanan[data->jumlah_pemesanan].kode_pemesanan, 100, 101);
		strcpy(data->pesanan[data->jumlah_pemesanan].nama_customer, data->customer[idx].nama);
		strcpy(data->pesanan[data->jumlah_pemesanan].nama_staff, data->staff[idx_staff].nama);
		strcpy(data->pesanan[data->jumlah_pemesanan].tgl_pertemuan, tgl);
		data->pesanan[data->jumlah_pemesanan].tgl_pertemuan[11] = '\0';
		data->pesanan[data->jumlah_pemesanan].durasi = jam;
		strcpy(data->pesanan[data->jumlah_pemesanan].status, "aktif");
		data->jumlah_pemesanan++;
		simpan_data_pemesanan(data);
		printf("\n Terima kasih sudah menggunakan jasa kami. Silakan menunggu dihubungi oleh staff yang telah kamu pilih untuk konfirmasi detil pertemuan.\n");
        printf("\n Tekan enter untuk melanjutkan.");
		return;
	}
	else
	{
		printf("\n Oke. Tekan enter untuk kembali ke akun anda!\n");
		return;
	}
}

int konversi_tanggal_ke_int(char *tanggal)
{
	char temp[11];
	temp[0] = tanggal[6];
	temp[1] = tanggal[7];
	temp[2] = tanggal[8];
	temp[3] = tanggal[9];
	temp[4] = tanggal[3];
	temp[5] = tanggal[4];
	temp[6] = tanggal[0];
	temp[7] = tanggal[1];
	temp[8] = '\0';
	return atoi(temp);
}

void tukar_data_staff(staff *data_1, staff *data_2){
	staff temp = *data_1;
	*data_1 = *data_2;
	*data_2 = temp;
	return;
}

void tukar_data_customer(customer *data_1, customer *data_2){
	customer temp = *data_1;
	*data_1 = *data_2;
	*data_2 = temp;
	return;
}

void tukar_data_pemesanan(pesanan *data_1, pesanan *data_2){
	pesanan temp = *data_1;
	*data_1 = *data_2;
	*data_2 = temp;
	return;
}

void urutkan_staff_sesuai_nama(rental *data, int status){
	int i;
	int flag;
	do{
		flag = 0;
		for(i = 0; i < data->jumlah_staff-1; i++){
			if(strcmp(data->staff[i].nama, data->staff[i+1].nama) > 0 && status == 1 )
            {
				tukar_data_staff(&data->staff[i], &data->staff[i+1]);
				flag = 1;
			}
			if(strcmp(data->staff[i].nama, data->staff[i+1].nama) < 0 && status == 2)
            {
				tukar_data_staff(&data->staff[i], &data->staff[i+1]);
				flag = 1;
			}
		}
	}
	while(flag == 1);
	return;
}

void urutkan_customer_sesuai_nama(rental *data, int status){
	int i;
	int flag;
	do{
		flag = 0;
		for(i = 0; i < data->jumlah_customer-1; i++){
			if(strcmp(data->customer[i].nama, data->customer[i+1].nama) > 0 && status == 1 )
            {
				tukar_data_customer(&data->customer[i], &data->customer[i+1]);
				flag = 1;
			}
			if(strcmp(data->customer[i].nama, data->customer[i+1].nama) < 0 && status == 2)
            {
				tukar_data_customer(&data->customer[i], &data->customer[i+1]);
				flag = 1;
			}
		}
	}
	while(flag == 1);
	return;
}

void urutkan_pemesanan_sesuai_tanggal(rental *data, int status)
{
	int i;
	int tanggal[data->jumlah_pemesanan];
	for(i = 0; i < data->jumlah_pemesanan; i++)
    {
		tanggal[i] = konversi_tanggal_ke_int(data->pesanan[i].tgl_pertemuan);
	}
	int flag;
	int temp;
	do
    {
		flag = 0;
		for(i = 0; i < data->jumlah_pemesanan-1; i++)
        {
			if(tanggal[i] > tanggal[i+1] && status == 1)
            {
				tukar_data_pemesanan(&data->pesanan[i], &data->pesanan[i+1]);
				flag = 1;
				temp = tanggal[i];
				tanggal[i] = tanggal[i+1];
				tanggal[i+1] = temp;
			}
			if(tanggal[i] < tanggal[i+1] && status == 2)
            {
				tukar_data_pemesanan(&data->pesanan[i], &data->pesanan[i+1]);
				flag = 1;
				temp = tanggal[i];
				tanggal[i] = tanggal[i+1];
				tanggal[i+1] = temp;
			}
		}
	}
	while(flag == 1);
	return;
}

void urutkan_data(rental *data, int status)
{
	int pilih;
	clrscr();
	header();
	printf(" Pilihan pengurutan data secara: \n");
	printf(" 1. Ascending\n");
	printf(" 2. Descending\n");
	printf(" Data akan diurutkan secara [1/2]: ");
	scanf("%d", &pilih);
	switch(status)
	{
        case 1 :
        {
            urutkan_staff_sesuai_nama(data, pilih);
            if(pilih == 1)
            {
                printf("\n Data staff telah diurutkan menurut nama lengkap secara ascending. Tekan ENTER untuk melanjutkan!");
                getch();
                return;
            }
            else if(pilih == 2)
            {
                printf("\n Data staff telah diurutkan menurut nama lengkap secara descending. Tekan ENTER untuk melanjutkan!");
                getch();
                return;
            }
        }
        case 2 :
        {
            urutkan_customer_sesuai_nama(data, pilih);
            if(pilih == 1)
            {
                printf("\n Data customer telah diurutkan menurut nama lengkap secara ascending. Tekan ENTER untuk melanjutkan!");
                getch();
                return;
            }
            else if(pilih == 2)
            {
                printf("\n Data customer telah diurutkan menurut nama lengkap secara descending. Tekan ENTER untuk melanjutkan!");
                getch();
                return;
            }
        }
        case 3 :
        {
            urutkan_pemesanan_sesuai_tanggal(data, pilih);
            if(pilih == 1)
            {
                printf("\n Data pemesanan telah diurutkan menurut tanggal pertemuan secara ascending. Tekan ENTER untuk melanjutkan!");
                getch();
            }
            else if(pilih == 2)
            {
                printf("\n Data pemesanan telah diurutkan menurut tanggal pertemuan secara descending. Tekan ENTER untuk melanjutkan!");
                getch();
                return;
            }
        }
	}
    return;
}

/*************************************************
 FUNGSI UNTUK OPERASI FILE (BACA DAN TULIS)
*************************************************/

void baca_data_staff(rental *data)
{
    int i;
    FILE *fstaff;
    fstaff = fopen("staff.txt", "r");
    if(fstaff == NULL)
    {
        printf(" ERROR loading file!");
        getch();
        exit(1);
    }
    fscanf(fstaff, "%d\n", &data->jumlah_staff);
    if(data->jumlah_staff > 0)
    {
        fscanf(fstaff, "===================================================\n");
        fscanf(fstaff, "=            DAFTAR STAFF \"GF RENTAL\"             =\n");
        fscanf(fstaff, "===================================================\n\n");
        fscanf(fstaff, "==========================================================================================================================================================================\n");
        fscanf(fstaff, "=  Nomor Staff  =    Nama Lengkap      =       Username       =  Password  =         Email           =   No. Telp   =  Tgl Lahir  =  Umur  =  Rating  =  ELO  =  Status  =\n");
        fscanf(fstaff, "==========================================================================================================================================================================\n");
        for(i = 0; i < data->jumlah_staff; i++)
        {
            fscanf(fstaff, "=");
            fscanf(fstaff, " %d =", &data->staff[i].staff_num);
            ubah_spasi(&data->staff[i].nama);
            fscanf(fstaff, " %s =", data->staff[i].nama);
            ubah_spasi(&data->staff[i].nama);
            fscanf(fstaff, " %s =", data->staff[i].username);
            fscanf(fstaff, " %s =", data->staff[i].pass);
            protect_pass(&data->staff[i].pass, 1);
            fscanf(fstaff, " %s =", data->staff[i].email);
            fscanf(fstaff, " %s =", data->staff[i].nomor);
            fscanf(fstaff, " %s =", data->staff[i].tgl_lahir);
            fscanf(fstaff, " %d =", &data->staff[i].umur);
            fscanf(fstaff, " %d =", &data->staff[i].rating);
            fscanf(fstaff, " %d =", &data->staff[i].elo);
            fscanf(fstaff, " %s =\n", data->staff[i].status);
        }
        fscanf(fstaff, "==========================================================================================================================================================================");
    }
    fclose(fstaff);
}

void baca_data_customer(rental *data)
{
    int i;
    FILE *fcustomer;
    fcustomer = fopen("customer.txt", "r");
    if(fcustomer == NULL)
    {
        printf("ERROR loading file!");
        getch();
        exit(1);
    }
    fscanf(fcustomer, "%d\n", &data->jumlah_customer);
    if(data->jumlah_customer > 0)
    {
        fscanf(fcustomer, "=================================================\n");
        fscanf(fcustomer, "=          DAFTAR CUSTOMER \"GF RENTAL\"          =\n");
        fscanf(fcustomer, "=================================================\n\n");
        fscanf(fcustomer, "================================================================================================================================================\n");
        fscanf(fcustomer, "=  Nomor Customer  =     Nama Lengkap      =       Username       =  Password  =         Email           =   No. Telp   =  Tgl Lahir  =  Umur  =\n");
        fscanf(fcustomer, "================================================================================================================================================\n");
        for(i = 0; i < data->jumlah_customer; i++)
        {
            fscanf(fcustomer, "=");
            fscanf(fcustomer, " %d =", &data->customer[i].customer_num);
            fscanf(fcustomer, " %s =", data->customer[i].nama);
            ubah_spasi(&data->customer[i].nama);
            fscanf(fcustomer, " %s =", data->customer[i].username);
            fscanf(fcustomer, " %s =", data->customer[i].pass);
            protect_pass(&data->customer[i].pass, 1);
            fscanf(fcustomer, " %s =", data->customer[i].email);
            fscanf(fcustomer, " %s =", data->customer[i].nomor);
            fscanf(fcustomer, " %s =", data->customer[i].tgl_lahir);
            fscanf(fcustomer, " %d =\n", &data->customer[i].umur);
        }
        fscanf(fcustomer, "================================================================================================================================================");
    }
    fclose(fcustomer);
}

void baca_data_riwayat_pemesanan(rental *data)
{
    int i;
    FILE *friwayat;
    friwayat = fopen("riwayat.txt", "r");
    fscanf(friwayat, "%d\n", &data->jumlah_pemesanan);
    fscanf(friwayat, "=================================================\n");
    fscanf(friwayat, "=        RIWAYAT PEMESANAN \"GF RENTAL\"          =\n");
    fscanf(friwayat, "=================================================\n\n");
    fscanf(friwayat, "=============================================================================================================================\n");
    fscanf(friwayat, "=  Kode Pemesanan  =      Nama Customer     =       Nama Staff       =  Tgl Pertemuan  =  Durasi pertemuan(jam)  =  Status  =\n");
    fscanf(friwayat, "=============================================================================================================================\n");
    for(i = 0; i < data->jumlah_pemesanan; i++)
    {
        fscanf(friwayat, "=");
        fscanf(friwayat, " %d =", &data->pesanan[i].kode_pemesanan);
        fscanf(friwayat, " %s =", data->pesanan[i].nama_customer);
        ubah_spasi(&data->pesanan[i].nama_customer);
        fscanf(friwayat, " %s =", data->pesanan[i].nama_staff);
        ubah_spasi(&data->pesanan[i].nama_staff);
        fscanf(friwayat, " %s =", data->pesanan[i].tgl_pertemuan);
        fscanf(friwayat, " %d =", &data->pesanan[i].durasi);
        fscanf(friwayat, " %s =\n", data->pesanan[i].status);
    }
    fscanf(friwayat, "=============================================================================================================================");
    fclose(friwayat);
}

void simpan_data_staff(rental *data)
{
    int i;
    FILE *fstaff;
    fstaff = fopen("staff.txt", "w");
    if(fstaff == NULL)
    {
        printf(" ERROR loading file!");
        getch();
        exit(1);
    }
    fprintf(fstaff, "%d\n", data->jumlah_staff);
    fprintf(fstaff, "===================================================\n");
    fprintf(fstaff, "=            DAFTAR STAFF \"GF RENTAL\"             =\n");
    fprintf(fstaff, "===================================================\n\n");
    fprintf(fstaff, "==========================================================================================================================================================================\n");
    fprintf(fstaff, "=  Nomor Staff  =    Nama Lengkap      =       Username       =  Password  =         Email           =   No. Telp   =  Tgl Lahir  =  Umur  =  Rating  =  ELO  =  Status  =\n");
    fprintf(fstaff, "==========================================================================================================================================================================\n");
    for(i = 0; i < data->jumlah_staff; i++)
    {
        fprintf(fstaff, "=");
        fprintf(fstaff, " %13d =", data->staff[i].staff_num);
        ubah_spasi(&data->staff[i].nama);
        fprintf(fstaff, " %20s =", data->staff[i].nama);
        ubah_spasi(&data->staff[i].nama);
        fprintf(fstaff, " %20s =", data->staff[i].username);
        protect_pass(&data->staff[i].pass, 0);
        fprintf(fstaff, " %10s =", data->staff[i].pass);
        protect_pass(&data->staff[i].pass, 1);
        fprintf(fstaff, " %23s =", data->staff[i].email);
        fprintf(fstaff, " %12s =", data->staff[i].nomor);
        fprintf(fstaff, " %11s =", data->staff[i].tgl_lahir);
        fprintf(fstaff, " %6d =", data->staff[i].umur);
        fprintf(fstaff, " %8d =", data->staff[i].rating);
        fprintf(fstaff, " %5d =", data->staff[i].elo);
        fprintf(fstaff, " %8s =\n", data->staff[i].status);
    }
    fprintf(fstaff, "==========================================================================================================================================================================");
    fclose(fstaff);
}

void simpan_data_customer(rental *data)
{
    int i;
    FILE *fcustomer;
    fcustomer = fopen("customer.txt", "w");
    if(fcustomer == NULL)
    {
        printf("ERROR loading file!");
        getch();
        exit(1);
    }
    fprintf(fcustomer, "%d\n", data->jumlah_customer);
    fprintf(fcustomer, "=================================================\n");
    fprintf(fcustomer, "=          DAFTAR CUSTOMER \"GF RENTAL\"          =\n");
    fprintf(fcustomer, "=================================================\n\n");
    fprintf(fcustomer, "================================================================================================================================================\n");
    fprintf(fcustomer, "=  Nomor Customer  =     Nama Lengkap      =       Username       =  Password  =         Email           =   No. Telp   =  Tgl Lahir  =  Umur  =\n");
    fprintf(fcustomer, "================================================================================================================================================\n");
    for(i=0; i < data->jumlah_customer; i++)
    {
        fprintf(fcustomer, "=");
        fprintf(fcustomer, " %16d =", data->customer[i].customer_num);
        ubah_spasi(&data->customer[i].nama);
        fprintf(fcustomer, " %21s =", data->customer[i].nama);
        ubah_spasi(&data->customer[i].nama);
        fprintf(fcustomer, " %20s =", data->customer[i].username);
        protect_pass(&data->customer[i].pass, 0);
        fprintf(fcustomer, " %10s =", data->customer[i].pass);
        protect_pass(&data->customer[i].pass, 1);
        fprintf(fcustomer, " %23s =", data->customer[i].email);
        fprintf(fcustomer, " %12s =", data->customer[i].nomor);
        fprintf(fcustomer, " %11s =", data->customer[i].tgl_lahir);
        fprintf(fcustomer, " %6d =\n", data->customer[i].umur);
    }
    fprintf(fcustomer, "================================================================================================================================================");
    fclose(fcustomer);
}

void simpan_data_pemesanan(rental *data)
{
    int i;
    FILE *friwayat;
    friwayat = fopen("riwayat.txt", "w");
    fprintf(friwayat, "%d\n", data->jumlah_pemesanan);
    fprintf(friwayat, "=================================================\n");
    fprintf(friwayat, "=        RIWAYAT PEMESANAN \"GF RENTAL\"          =\n");
    fprintf(friwayat, "=================================================\n\n");
    fprintf(friwayat, "=============================================================================================================================\n");
    fprintf(friwayat, "=  Kode Pemesanan  =      Nama Customer     =       Nama Staff       =  Tgl Pertemuan  =  Durasi pertemuan(jam)  =  Status  =\n");
    fprintf(friwayat, "=============================================================================================================================\n");
    for(i=0; i < data->jumlah_pemesanan; i++)
    {
        fprintf(friwayat, "=");
        fprintf(friwayat, " %16d =", data->pesanan[i].kode_pemesanan);
        ubah_spasi(&data->pesanan[i].nama_customer);
        fprintf(friwayat, " %22s =", data->pesanan[i].nama_customer);
        ubah_spasi(&data->pesanan[i].nama_customer);
        ubah_spasi(&data->pesanan[i].nama_staff);
        fprintf(friwayat, " %22s =", data->pesanan[i].nama_staff);
        ubah_spasi(&data->pesanan[i].nama_staff);
        fprintf(friwayat, " %15s =", data->pesanan[i].tgl_pertemuan);
        fprintf(friwayat, " %23d =", data->pesanan[i].durasi);
        fprintf(friwayat, " %8s =\n", data->pesanan[i].status);
    }
    fprintf(friwayat, "=============================================================================================================================");
    fclose(friwayat);
}

/*************************************************
 FUNGSI MENU ADMIN
*************************************************/

void menu_data_staff(rental *data)
{
    int i;
    urutkan_data(data, 1);
    clrscr();
    header();
    printf(" =================================================\n");
    printf(" =           DAFTAR STAFF \"GF RENTAL\"          =\n");
    printf(" =================================================\n\n");
    printf(" ================================================================================================================================================================\n");
    printf(" =  Nomor Staff  =      Nama Lengkap      =       Username       =         Email           =   No. Telp   =  Tgl Lahir  =  Umur  =  Rating  =  Tarif (per jam)  =\n");
    printf(" ================================================================================================================================================================\n");
    if(data->jumlah_staff > 0)
    {
        for(i=0; i < data->jumlah_staff; i++)
        {
            printf(" =");
            printf(" %13d =", data->staff[i].staff_num);
            printf(" %22s =", data->staff[i].nama);
            printf(" %20s =", data->staff[i].username);
            printf(" %23s =", data->staff[i].email);
            printf(" %12s =", data->staff[i].nomor);
            printf(" %11s =", data->staff[i].tgl_lahir);
            printf(" %6d =", data->staff[i].umur);
            printf(" %6d/5 =", data->staff[i].rating);
            printf(" %14d =\n", data->staff[i].tarif);
        }
    }
    else
        printf(" =                                       Belum ada staff yang terdaftar                                                                                         =\n");
    printf(" ================================================================================================================================================================\n");
    printf(" \n Tekan ENTER untuk kembali! ");
    return;
}

void menu_data_customer(rental *data)
{
    int i;
    urutkan_data(data, 2);
    clrscr();
    header();
    printf(" =================================================\n");
    printf(" =        DAFTAR CUSTOMER \"GF RENTAL\"          =\n");
    printf(" =================================================\n\n");
    printf(" ===================================================================================================================================================\n");
    printf(" =  Nomor Customer  =      Nama Lengkap      =       Username       =  Password  =         Email           =    No. Telp    =  Tgl Lahir  =  Umur  =\n");
    printf(" ===================================================================================================================================================\n");
    if(data->jumlah_customer > 0)
    {
        for(i=0; i < data->jumlah_customer; i++)
        {
            printf(" =");
            printf(" %16d =", data->customer[i].customer_num);
            printf(" %22s =", data->customer[i].nama);
            printf(" %20s =", data->customer[i].username);
            printf(" %10s =", data->customer[i].pass);
            printf(" %22s =", data->customer[i].email);
            printf(" %12s =", data->customer[i].nomor);
            printf(" %11s =", data->customer[i].tgl_lahir);
            printf(" %6d =\n", data->customer[i].umur);
        }
    }
    else
        printf(" =                                        Belum ada customer yang terdaftar                                                                        =\n");
    printf(" ===================================================================================================================================================\n");
    printf(" \n Tekan ENTER untuk kembali! ");
    return;
}

void menu_riwayat_pemesanan_semua(rental *data)
{
    int i;
    urutkan_data(data, 3);
    clrscr();
    header();
    printf(" =================================================\n");
    printf(" =        RIWAYAT PEMESANAN \"GF RENTAL\"        =\n");
    printf(" =================================================\n\n");
    printf(" =============================================================================================================================\n");
    printf(" =  Kode Pemesanan  =      Nama Customer     =       Nama Staff       =  Tgl Pertemuan  =  Durasi pertemuan(jam)  =  Status  =\n");
    printf(" =============================================================================================================================\n");
    if(data->jumlah_pemesanan > 0)
    {
        for(i=0; i < data->jumlah_pemesanan; i++)
        {
            printf(" =");
            printf(" %16d =", data->pesanan[i].kode_pemesanan);
            printf(" %22s =", data->pesanan[i].nama_customer);
            printf(" %22s =", data->pesanan[i].nama_staff);
            printf(" %15s =", data->pesanan[i].tgl_pertemuan);
            printf(" %22d =", data->pesanan[i].durasi);
            printf(" %8s =\n", data->pesanan[i].status);
        }
    }
    else
        printf(" =                                                       Belum ada pemesanan                                                 =\n");
    printf(" =============================================================================================================================\n");
    printf(" \n Tekan ENTER untuk kembali! ");
    return;
}

void menu_konfirmasi_pendaftaran_staff(rental *data)
{
    int i, nomor;
    int flag = 0;
    int jmlh_staff_pending = 0;
    int idx[MAX_STAFF];
    for(i = 0; i < data->jumlah_staff; i++)
    {
        if(strcmp(&data->staff[i].status, "pending") == 0)
        {
            idx[jmlh_staff_pending] = i;
            jmlh_staff_pending++;
        }
    }
    clrscr();
    header();
    printf(" =================================================\n");
    printf(" = DAFTAR STAFF DENGAN STATUS PENDING \"GF RENTAL\"=\n");
    printf(" =================================================\n\n");
    printf(" =================================================================================================================================\n");
    printf(" =  Nomor Staff  =      Nama Lengkap      =       Username       =         Email           =   No. Telp   =  Tgl Lahir  =  Umur  =\n");
    printf(" =================================================================================================================================\n");
    if(jmlh_staff_pending > 0)
    {
        for(i=0; i < jmlh_staff_pending; i++)
        {
            printf(" =");
            printf(" %13d =", data->staff[idx[i]].staff_num);
            printf(" %22s =", data->staff[idx[i]].nama);
            printf(" %20s =", data->staff[idx[i]].username);
            printf(" %23s =", data->staff[idx[i]].email);
            printf(" %12s =", data->staff[idx[i]].nomor);
            printf(" %11s =", data->staff[idx[i]].tgl_lahir);
            printf(" %6d =\n", data->staff[idx[i]].umur);
        }
        printf(" =================================================================================================================================\n");
        do
        {
            printf("\n Pilih nomor staff yang ingin di konfirmasi : ");
            scanf("%d", &nomor);
            for(i = 0; i < jmlh_staff_pending; i++)
            {
                if(nomor == data->staff[idx[i]].staff_num)
                {
                    int index = idx[i];
                    flag = 1;
                    strcpy(data->staff[index].status, "aktif");
                    data->staff[index].elo += 1000;
                    simpan_data_staff(data);
                    printf("\n Anda telah berhasil mengkonfirmasi akun milik %s.\n", data->staff[index].nama);
                    i = jmlh_staff_pending;
                }
            }
        }
        while(flag == 0);
    }
    else
    {
        printf(" =                                              Belum ada staff yang berstatus pending                                           =\n");
        printf(" =================================================================================================================================\n");
    }
    printf(" \n Tekan ENTER untuk kembali! ");
    return;
}

/*************************************************
 FUNGSI MENU STAFF
*************************************************/

void menu_daftar_pesanan(rental *data, int idx)
{
    int i, jmlh_pesanan = 0;
    int index[MAX_PEMESANAN_PER_STAFF];
    urutkan_data(data, 3);
    for(i = 0; i < data->jumlah_pemesanan; i++)
    {
        if(strcmp(data->pesanan[i].nama_staff, data->staff[idx].nama) == 0 && strcmp(data->pesanan[i].status, "aktif") == 0)
        {
            index[jmlh_pesanan] = i;
            jmlh_pesanan++;
        }
    }
    clrscr();
    header();
    printf(" =================================================\n");
    printf(" =        DAFTAR PESANAN AKTIF \"GF RENTAL\"       =\n");
    printf(" =================================================\n\n");
    printf(" =======================================================================================================\n");
    printf(" =  Kode Pemesanan  =       Nama Customer       =  Tgl Pertemuan  =  Durasi pertemuan(jam)  =  Status  =\n");
    printf(" =======================================================================================================\n");
    if(jmlh_pesanan > 0)
    {
        for(i=0; i < jmlh_pesanan; i++)
        {
            printf(" =");
            printf(" %16d =", data->pesanan[index[i]].kode_pemesanan);
            printf(" %25s =", data->pesanan[index[i]].nama_customer);
            printf(" %15s =", data->pesanan[index[i]].tgl_pertemuan);
            printf(" %23d =", data->pesanan[index[i]].durasi);
            printf(" %8s =\n", data->pesanan[index[i]].status);
        }
    }
    else
        printf(" =                                            Belum ada pemesanan                                      =\n");
    printf(" =======================================================================================================\n");
    printf(" \n Tekan ENTER untuk kembali! ");
    return;
}

void menu_edit_data_diri_staff(rental *data, int idx)
{
    int num,i;
	clrscr();
	header();
	printf(" Data anda saat ini :\n\n");
	printf(" Nama         : %s\n", data->staff[idx].nama);
    printf(" Username     : %s\n", data->staff[idx].username);
    printf(" Password     : %s\n", data->staff[idx].pass);
    printf(" Email        : %s\n", data->staff[idx].email);
    printf(" Nomor telepon: %s\n", data->staff[idx].nomor);
    printf(" Tanggal Lahir: %s\n", data->staff[idx].tgl_lahir);
    printf(" Umur         : %d\n\n", data->staff[idx].umur);
    printf(" Data yang baru:\n\n");
    printf(" Nama Lengkap [maks. 20 karakter]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->staff[idx].nama);
    printf(" Username [maks. 20 karakter tanpa spasi]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->staff[idx].username);
    printf(" Password [maks 10 karakter]: ");
    scanf("%s", data->staff[idx].pass);
    printf(" E-mail : ");
    scanf("%s", data->staff[idx].email);
    do
    {
        printf(" No. telp : ");
        scanf("%s", data->staff[idx].nomor);
    }
    while(cek_format_nomor_telepon(&data->staff[idx].nomor, strlen(data->staff[idx].nomor)) == 0);
    do
    {
        printf(" Tanggal Lahir [DD/MM/YYYY]: ");
        scanf("%s", data->staff[idx].tgl_lahir);
    }
    while(cek_format_tanggal(&data->staff[idx].tgl_lahir) == 0);
    printf(" Umur : ");
    scanf("%d", &data->staff[idx].umur);
    printf("\n Tekan ENTER untuk melanjutkan ");
    getch();
    simpan_data_staff(data);
    printf("\n\n Akun anda telah disimpan!");
    return;
}

/*************************************************
 FUNGSI MENU CUSTOMER
*************************************************/

void menu_list_staff_yang_tersedia(rental *data, int idx)
{
    int i;
    char opt;
    int flag = 0;
    int jmlh_staff_tersedia = 0;
    int idx_staff[MAX_STAFF];
    urutkan_data(data, 1);
    for(i = 0; i < data->jumlah_staff; i++)
    {
        if(strcmp(data->staff[i].status, "aktif") == 0)
        {
            idx_staff[jmlh_staff_tersedia] = i;
            jmlh_staff_tersedia++;
        }
    }
    clrscr();
    header();
    printf(" =================================================\n");
    printf(" =           DAFTAR STAFF \"GF RENTAL\"            =\n");
    printf(" =================================================\n\n");
    printf(" ================================================================================================================================================================\n");
    printf(" =  Nomor Staff  =      Nama Lengkap      =       Username       =         Email           =   No. Telp   =  Tgl Lahir  =  Umur  =  Rating  =  Tarif (per jam)  =\n");
    printf(" ================================================================================================================================================================\n");
    if(jmlh_staff_tersedia > 0)
    {
        for(i=0; i < jmlh_staff_tersedia; i++)
        {
            printf(" =");
            printf(" %13d =", data->staff[idx_staff[i]].staff_num);
            printf(" %22s =", data->staff[idx_staff[i]].nama);
            printf(" %20s =", data->staff[idx_staff[i]].username);
            printf(" %23s =", data->staff[idx_staff[i]].email);
            printf(" %12s =", data->staff[idx_staff[i]].nomor);
            printf(" %11s =", data->staff[idx_staff[i]].tgl_lahir);
            printf(" %6d =", data->staff[idx_staff[i]].umur);
            if(data->staff[idx_staff[i]].rating == 0)
                printf(" %8s =", "N/A");
            else
                printf(" %6d/5 =", data->staff[idx_staff[i]].rating);
            hitung_tarif(&data->staff[idx_staff[i]].tarif, &data->staff[idx_staff[i]].elo);
            printf(" %17d =\n", data->staff[idx_staff[i]].tarif);
        }
    }
    else
        printf(" =                                       Belum ada staff yang tersedia                                                                                          =\n");
    printf(" ================================================================================================================================================================\n");
    do
    {
        printf("\n Apakah kamu tertarik untuk membuat pertemuan dengan staff kami [Y/N]? ");
        fflush(stdin);
        scanf("%c", &opt);
        opt = toupper(opt);
    }
    while(opt != 'Y' && opt != 'N');
    if(opt == 'Y')
        konfirmasi_rental(data, idx);
    return;
}

void menu_riwayat_pemesanan_customer(rental *data, int idx)
{
    int i, jmlh_pesanan = 0;
    int index[MAX_PEMESANAN_PER_CUSTOMER];
    urutkan_data(data, 3);
    for(i = 0; i < data->jumlah_pemesanan; i++)
    {
        if(strcmp(data->pesanan[i].nama_customer, data->customer[idx].nama) == 0)
        {
            index[jmlh_pesanan] = i;
            jmlh_pesanan++;
        }
    }
    clrscr();
    header();
    printf(" =================================================\n");
    printf(" =        RIWAYAT PEMESANAN \"GF RENTAL\"          =\n");
    printf(" =================================================\n\n");
    printf(" ====================================================================================================\n");
    printf(" =  Kode Pemesanan  =       Nama Staff       =  Tgl Pertemuan  =  Durasi pertemuan(jam)  =  Status  =\n");
    printf(" ====================================================================================================\n");
    if(jmlh_pesanan > 0)
    {
        for(i=0; i < jmlh_pesanan; i++)
        {
            printf(" =");
            printf(" %16d =", data->pesanan[index[i]].kode_pemesanan);
            printf(" %22s =", data->pesanan[index[i]].nama_staff);
            printf(" %15s =", data->pesanan[index[i]].tgl_pertemuan);
            printf(" %22d =", data->pesanan[index[i]].durasi);
            printf(" %8s =\n", data->pesanan[index[i]].status);
        }
    }
    else
        printf(" =                                           Belum ada pemesanan                                    =\n");
    printf(" ====================================================================================================\n");
    printf(" \n Tekan ENTER untuk kembali! ");
    return;
}

void menu_rating_staff_yang_pernah_dipesan(rental *data, int idx)
{
    int i, j;
    char opt;
    int flag = 0;
    int jmlh_pesanan_aktif = 0;
    int jmlh_staff_dipesan = 0;
    int idx_pemesanan[MAX_PEMESANAN_PER_CUSTOMER];
    int idx_staff[MAX_STAFF];
    int nomor, rating;
    for(i = 0; i < data->jumlah_pemesanan; i++)
    {
        if(strcmp(data->pesanan[i].status, "aktif") == 0 &&  strcmp(data->pesanan[i].nama_customer, data->customer[idx].nama) == 0)
        {
            idx_pemesanan[jmlh_pesanan_aktif] = i;
            jmlh_pesanan_aktif++;
        }
    }
    for(i = 0; i < jmlh_pesanan_aktif; i++)
    {
        for(j = 0; j < data->jumlah_staff; j++)
        {
            if(strcmp(data->pesanan[idx_pemesanan[i]].nama_staff, data->staff[j].nama) == 0)
            {
                idx_staff[jmlh_staff_dipesan] = j;
                jmlh_staff_dipesan++;
            }
        }
    }
    clrscr();
    header();
    printf(" ========================================\n");
    printf(" =     DAFTAR STAFF \"GF RENTAL\"         =\n");
    printf(" ========================================\n\n");
    printf(" ========================================\n");
    printf(" =  Nomor Staff  =       Username       =\n");
    printf(" ========================================\n");
    if(jmlh_staff_dipesan > 0)
    {
        for(i=0; i < jmlh_staff_dipesan; i++)
        {
            printf(" =");
            printf(" %13d =", data->staff[idx_staff[i]].staff_num);
            printf(" %20s =\n", data->staff[idx_staff[i]].username);
        }
        printf(" ========================================\n");
        printf("\n Masukkan nomor staff yang ingin anda berikan rating: ");
        scanf ("%d", &nomor);
        for(i = 0; i < jmlh_staff_dipesan; i++)
        {
            if(data->staff[idx_staff[i]].staff_num == nomor)
            {
                do
                {
                    printf("\n Masukkan rating [1-5]: ");
                    scanf("%d", &rating);
                }
                while(rating < 1 || rating > 5);
                printf("\n Dengan memberikan rating, janji temu anda dengan staff tersebut akan dianggap selesai.");
                do
                {
                    printf("\n Apakah anda ingin melanjutkan [Y/N]? ");
                    fflush(stdin);
                    scanf("%c", &opt);
                    opt = toupper(opt);
                }
                while(opt != 'Y' && opt != 'N');
                if(opt == 'Y')
                {
                    rate_staff(data, rating, idx_staff[i]);
                    for(j = 0; j < jmlh_pesanan_aktif; j++)
                    {
                        if(strcmp(data->staff[idx_staff[i]].nama, data->pesanan[idx_pemesanan[j]].nama_staff) == 0)
                        {
                            strcpy(data->pesanan[idx_pemesanan[j]].status, "selesai");
                            simpan_data_pemesanan(data);
                        }
                    }
                    printf("\n Anda telah berhasil memberi bintang %d pada %s!", rating, data->staff[idx_staff[i]].nama);
                }
                printf("\n Tekan ENTER untuk kembali! ");
                return;
            }
        }

    }
    else
    {
        printf(" =  Belum ada staff yang dapat dirate   =\n");
        printf(" ========================================\n");
    }
    return;
}

void menu_edit_data_diri_customer(rental *data, int idx)
{
    int num,i;
	clrscr();
	header();
	printf(" Data anda saat ini :\n\n");
	printf(" Nama         : %s\n", data->customer[idx].nama);
    printf(" Username     : %s\n", data->customer[idx].username);
    printf(" Password     : %s\n", data->customer[idx].pass);
    printf(" Email        : %s\n", data->customer[idx].email);
    printf(" Nomor telepon: %s\n", data->customer[idx].nomor);
    printf(" Tanggal Lahir: %s\n", data->customer[idx].tgl_lahir);
    printf(" Umur         : %d\n\n", data->customer[idx].umur);
    printf(" Data yang baru:\n\n");
    printf(" Nama Lengkap [maks. 20 karakter]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->customer[idx].nama);
    printf(" Username [maks. 20 karakter tanpa spasi]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->customer[idx].username);
    printf(" Password [maks 10 karakter]: ");
    scanf("%s", data->customer[idx].pass);
    printf(" E-mail : ");
    scanf("%s", data->customer[idx].email);
    do
    {
        printf(" No. telp : ");
        scanf("%s", data->customer[idx].nomor);
    }
    while(cek_format_nomor_telepon(&data->customer[idx].nomor, strlen(data->customer[idx].nomor)) == 0);
    do
    {
        printf(" Tanggal Lahir [DD/MM/YYYY]: ");
        scanf("%s", data->customer[idx].tgl_lahir);
    }
    while(cek_format_tanggal(&data->customer[idx].tgl_lahir) == 0);
    printf(" Umur : ");
    scanf("%d", &data->customer[idx].umur);
    printf("\n Tekan ENTER untuk melanjutkan ");
    getch();
    simpan_data_customer(data);
    printf("\n\n Akun anda telah disimpan!");
    return;
}

/*************************************************
 FUNGSI MENU UTAMA
*************************************************/

void menu_admin(rental *data)
{
    int pilihan_menu;
    do
    {
        clrscr();
        header();
        printf(" Welcome back!\n\n");
        printf(" ===== MENU ADMIN =====\n\n");
        printf(" 1. Data staff\n");
        printf(" 2. Data customer\n");
        printf(" 3. Riwayat pemesanan\n");
        printf(" 4. Konfirmasi pendaftaran staff\n");
        printf(" 5. Logout\n\n");
        printf(" Pilihan Anda : ");
        scanf("%d", &pilihan_menu);
        switch(pilihan_menu)
        {
            case 1:
            {
                menu_data_staff(data);
                getch();
                break;
            }
            case 2:
            {
                menu_data_customer(data);
                getch();
                break;
            }
            case 3:
            {
                menu_riwayat_pemesanan_semua(data);
                getch();
                break;
            }
            case 4:
            {
                menu_konfirmasi_pendaftaran_staff(data);
                getch();
                break;
            }
        }
    }
    while(pilihan_menu != 5);
    main();
}

void menu_staff(rental *data, int idx)
{
    int pilihan_menu;
    do
    {
        clrscr();
        header();
        printf(" Welcome back %s!\n\n", data->staff[idx].nama);
        printf(" ===== MENU STAFF =====\n\n");
        printf(" 1. Daftar pesanan\n");
        printf(" 2. Edit data diri\n");
        printf(" 3. Logout\n\n");
        printf(" Pilihan Anda : ");
        scanf("%d", &pilihan_menu);
        switch(pilihan_menu)
        {
            case 1:
            {
                menu_daftar_pesanan(data, idx);
                getch();
                break;
            }
            case 2:
            {
                menu_edit_data_diri_staff(data, idx);
                getch();
                break;
            }
        }
    }
    while(pilihan_menu != 3);
    main();
}

void menu_customer(rental *data, int idx)
{
    int pilihan_menu;
    do
    {
        clrscr();
        header();
        printf(" Welcome back %s!\n\n", data->customer[idx].nama);
        printf(" ===== MENU CUSTOMER =====\n\n");
        printf(" 1. List staff yang tersedia\n");
        printf(" 2. Riwayat pemesanan\n");
        printf(" 3. Rating staff yang pernah dipesan\n");
        printf(" 4. Edit data diri\n");
        printf(" 5. Logout\n\n");
        printf(" Pilihan Anda : ");
        scanf("%d", &pilihan_menu);
        switch(pilihan_menu)
        {
            case 1 :
            {
                menu_list_staff_yang_tersedia(data, idx);
                getch();
                break;
            }
            case 2 :
            {
                menu_riwayat_pemesanan_customer(data, idx);
                getch();
                break;
            }
            case 3 :
            {
                menu_rating_staff_yang_pernah_dipesan(data, idx);
                getch();
                break;
            }
            case 4 :
            {
                menu_edit_data_diri_customer(data, idx);
                getch();
                break;
            }
        }
    }
    while(pilihan_menu != 5);
    main();
}

/*************************************************
 FUNGSI LOGIN
*************************************************/

void admin_login(rental *data)
{
    int i, flag = 0;
    char username[] = "Admin";
    char pass[] = "jomblo";
    char u[25], p[8];
    do
    {
        clrscr();
        header();
        printf(" ===== Login Admin =====\n\n");
        printf(" Username\t: ");
        fflush(stdin);
        scanf("%[^\n]s", u);
        printf(" Password\t: ");
        scanf("%s", p);
        if(strcmp(u, username) == 0 && strcmp(p, pass) == 0)
        {
            flag = 1;
        }
        if(flag == 0)
        {
            printf("\n Username atau password anda salah.");
            getch();
        }
    }
    while(flag == 0);
    printf("\n Berhasil login.");
    getch();
    menu_admin(data);
}

void staff_login(rental *data)
{
    int i, idx_akun, flag = 0;
    char u[25], p[10];
    do
    {
        clrscr();
        header();
        printf(" ===== Login Staff =====\n\n");
        printf(" Username\t: ");
        fflush(stdin);
        scanf("%[^\n]s", u);
        printf(" Password\t: ");
        scanf("%s", p);
        for(i = 0; i < data->jumlah_staff; i++)
        {
            if(strcmp(u, data->staff[i].username) == 0 && strcmp(p, data->staff[i].pass) == 0)
            {
                if(strcmp(data->staff[i].status, "pending") == 0)
                {
                    printf("\n Akun anda masih belum dikonfirmasi oleh admin. Mohon kembali lagi di lain waktu.\n");
                    printf(" Tekan ENTER untuk kembali! ");
                    return;
                }
                flag = 1;
                idx_akun = i;
            }
        }
        if(flag == 0)
        {
            printf("\n Username atau password anda salah.");
            getch();
        }
    }
    while(flag == 0);
    printf("\n Berhasil login.");
    getch();
    menu_staff(data, idx_akun);
}

void customer_login(rental *data)
{
    int i, idx_akun, flag = 0;
    char u[25], p[10];
    do
    {
        clrscr();
        header();
        printf(" ===== Login Customer =====\n\n");
        printf(" Username\t: ");
        fflush(stdin);
        scanf("%[^\n]s", u);
        printf(" Password\t: ");
        scanf("%s", p);
        for(i = 0; i < data->jumlah_customer; i++)
        {
            if(strcmp(u, data->customer[i].username) == 0 && strcmp(p, data->customer[i].pass) == 0)
            {
                flag = 1;
                idx_akun = i;
            }
        }
        if(flag == 0)
        {
            printf("\n Username atau password anda salah.");
            getch();
        }
    }
    while(flag == 0);
    printf("\n Berhasil login.");
    getch();
    menu_customer(data, idx_akun);
}

/*************************************************
 FUNGSI CREATE ACCOUNT
*************************************************/

void create_staff_account(rental *data)
{
    clrscr();
    header();
    printf(" ===== Create Staff Account =====\n\n");
    printf(" Nama Lengkap [maks. 20 karakter]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->staff[data->jumlah_staff].nama);
    printf(" Username [maks. 20 karakter tanpa spasi]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->staff[data->jumlah_staff].username);
    printf(" Password : ");
    scanf("%s", data->staff[data->jumlah_staff].pass);
    printf(" E-mail : ");
    scanf("%s", data->staff[data->jumlah_staff].email);
    do
    {
        printf(" No. telp : ");
        scanf("%s", data->staff[data->jumlah_staff].nomor);
    }
    while(cek_format_nomor_telepon(&data->staff[data->jumlah_staff].nomor, strlen(data->staff[data->jumlah_staff].nomor)) == 0);
    do
    {
        printf(" Tanggal Lahir [DD/MM/YYYY]: ");
        scanf("%s", data->staff[data->jumlah_staff].tgl_lahir);
    }
    while(cek_format_tanggal(&data->staff[data->jumlah_staff].tgl_lahir) == 0);
    printf(" Umur : ");
    scanf("%d", &data->staff[data->jumlah_staff].umur);
    printf("\n Tekan ENTER untuk melanjutkan ");
    getch();
    disclaimer();
    strcpy(data->staff[data->jumlah_staff].status, "pending");
    data->staff[data->jumlah_staff].rating = 0;
    data->staff[data->jumlah_staff].elo = 0;
    data->staff[data->jumlah_staff].tarif = 0;
    generate_number(&data->staff[data->jumlah_staff].staff_num, 100, 101);
    data->jumlah_staff++;
    simpan_data_staff(data);
    printf("\n\n Akun anda akan diverifikasi terlebih dahulu oleh admin. Proses verifikasi akan membutuhkan maksimal 24 jam. Silakan cek kembali lain waktu!.\n");
    return;
}

void create_customer_account(rental *data)
{
    clrscr();
    header();
    printf(" ===== Create Customer Account =====\n\n");
    printf(" Nama Lengkap [maks. 20 karakter]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->customer[data->jumlah_customer].nama);
    printf(" Username [maks. 20 karakter tanpa spasi]: ");
    fflush(stdin);
    scanf("%[^\n]s", data->customer[data->jumlah_customer].username);
    printf(" Password [maks 10 karakter]: ");
    scanf("%s", data->customer[data->jumlah_customer].pass);
    printf(" E-mail : ");
    scanf("%s", data->customer[data->jumlah_customer].email);
    do
    {
        printf(" No. telp : ");
        scanf("%s", data->customer[data->jumlah_customer].nomor);
    }
    while(cek_format_nomor_telepon(&data->customer[data->jumlah_customer].nomor, strlen(data->customer[data->jumlah_customer].nomor)) == 0);
    do
    {
        printf(" Tanggal Lahir [DD/MM/YYYY]: ");
        scanf("%s", data->customer[data->jumlah_customer].tgl_lahir);
    }
    while(cek_format_tanggal(&data->customer[data->jumlah_customer].tgl_lahir) == 0);
    printf(" Umur : ");
    scanf("%d", &data->customer[data->jumlah_customer].umur);
    printf("\n Tekan ENTER untuk melanjutkan ");
    getch();
    disclaimer();
    generate_number(&data->customer[data->jumlah_customer].customer_num, 100, 101);
    data->jumlah_customer++;
    simpan_data_customer(data);
    printf("\n\n Akun anda telah terdaftar!");
    getch();
    customer_login(data);
}

/*************************************************
 FUNGSI MAIN
*************************************************/

void main()
{
    config();
    rental data;
    inisialisasi_struct(&data);
    baca_data_staff(&data);
    baca_data_customer(&data);
    baca_data_riwayat_pemesanan(&data);
    int pilihan_menu;
    char opt;
    do
    {
        clrscr();
        header();
        printf(" ===== MENU UTAMA =====\n\n");
        printf(" 1. ADMIN\n");
        printf(" 2. STAFF\n");
        printf(" 3. CUSTOMER\n");
        printf(" 0. EXIT\n\n");
        printf(" Pilihan Anda : ");
        scanf("%d", &pilihan_menu);
        switch(pilihan_menu)
        {
            case 1 :
            {
                admin_login(&data);
                getch();
                break;
            }
            case 2 :
            {
                do
                {
                    printf("\n Sudah punya akun [Y/N]? ");
                    fflush(stdin);
                    scanf("%c", &opt);
                    opt = toupper(opt);
                }
                while(opt != 'Y' && opt != 'N');
                if(opt == 'Y')
                    staff_login(&data);
                else
                    create_staff_account(&data);
                getch();
                break;
            }
            case 3 :
            {
                do
                {
                    printf("\n Sudah punya akun [Y/N]? ");
                    fflush(stdin);
                    scanf("%c", &opt);
                    opt = toupper(opt);
                }
                while(opt != 'Y' && opt != 'N');
                if(opt == 'Y')
                    customer_login(&data);
                else
                    create_customer_account(&data);
                getch();
                break;
            }
        }
    }
    while(pilihan_menu != 0);
    simpan_data_staff(&data);
    simpan_data_customer(&data);
    simpan_data_pemesanan(&data);
    clrscr();
    printf("\n Terima kasih karena telah menggunakan layanan kami!\n");
    printf("\n Sampai jumpa =D\n");
    getch();
    exit(0);
}
