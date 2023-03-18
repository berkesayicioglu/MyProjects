import java.util.Scanner;

public class Book {
	protected String bookId, bookName,genre,author,publishdate;
	
	public Book() {
		this.bookId = "";
		this.bookName = "";
		this.author = "";
		this.genre= "";
		this.publishdate = "";
	}
	
	
	public Book(String bookId, String bookName, String genre, String author, String publishdate) {
		super();
		this.bookId = bookId;
		this.bookName = bookName;
		this.genre = genre;
		this.author = author;
		this.publishdate = publishdate;
	}


	public void getInput() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the Book Name: ");
		bookName = sc.nextLine();
		System.out.println("Enter the author: ");
		author = sc.nextLine();
		System.out.println("Enter the genre: ");
		genre = sc.nextLine();
		System.out.println("Enter the publish date: ");
		publishdate = sc.next();
	}
	
	public boolean checkId(String bookId) {
		if(this.bookId.equalsIgnoreCase(bookId))
			return true; //book exists
		return false;
	}


	@Override
	public String toString() {
		return "Book \nBookId=" + bookId + 
				"\nBook Name= " + bookName + 
				"\nGenre= " + genre + 
				"\nAuthor= " + author + 
				"\nPublish date= " + publishdate + "\n";
	}


	public String getBookId() {
		return bookId;
	}


	public void setBookId(String bookId) {
		this.bookId = bookId;
	}


	public String getBookName() {
		return bookName;
	}


	public void setBookName(String bookName) {
		this.bookName = bookName;
	}


	public String getGenre() {
		return genre;
	}


	public void setGenre(String genre) {
		this.genre = genre;
	}


	public String getAuthor() {
		return author;
	}


	public void setAuthor(String author) {
		this.author = author;
	}


	public String getPublishdate() {
		return publishdate;
	}


	public void setPublishdate(String publishdate) {
		this.publishdate = publishdate;
	}

	

	
}
