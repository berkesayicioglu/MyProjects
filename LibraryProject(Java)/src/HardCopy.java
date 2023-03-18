import java.util.Scanner;

public class HardCopy extends Book{
	private double bookPrice;
	private String locationId;
	
	public HardCopy() {
		super();
	}
	
	public HardCopy(String bookId, String bookName, String author, String genre, String publishDate, double bookPrice, String locationId) {
		super(bookId, bookName, author, genre, publishDate);
		this.bookPrice = bookPrice;
		this.locationId = locationId;
	}

	public double getBookPrice() {
		return bookPrice;
	}

	public void setBookPrice(double bookPrice) {
		this.bookPrice = bookPrice;
	}

	public String getLocationId() {
		return locationId;
	}

	public void setLocationId(String locationId) {
		this.locationId = locationId;
	}
	
	public void getInput() {
		Scanner sc = new Scanner(System.in);
		super.getInput();
		System.out.println("Enter the Book Price:");
		bookPrice = sc.nextDouble();
		System.out.println("Enter the Location Id:");
		locationId = sc.nextLine();
	}
	
	public String toString() {
		return "HardCopy\n" + super.toString()
				+ "\nBook Price = " + bookPrice
				+ "\nLocation Id = " + locationId;
	}
}
