
import java.util.Scanner;

public class Person {
	protected String nameSurname;
	protected int personId;
	protected String borrowDate;
	protected String phoneNo;
	protected String email;
	protected int numOfPeople;
	
	public Person() {
		super();
	}

	public Person(String nameSurname, int personId, String borrowDate, String phoneNo, String email) {
		super();
		this.nameSurname = nameSurname;
		this.personId = personId;
		this.borrowDate = borrowDate;
		this.phoneNo = phoneNo;
		this.email = email;
	}

	public int getPersonId() {
		return personId;
	}
	
	public String getBorrowDate() {
		return borrowDate;
	}

	public String getNameSurname(){
		return nameSurname;
	}

	public String getPhoneNo(){
		return phoneNo;
	}

	public String getEmail(){
		return email;
	}

	public void setPersonId(int personId) {
		this.personId = personId;
	}

	public void setBorrowDate(String borrowDate) {
		this.borrowDate = borrowDate;
	}

	public void setNameSurname(String nameSurname) {
		this.nameSurname = nameSurname;
	}

	public void setPhoneNo(String phoneNo) {
		this.phoneNo = phoneNo;
	}

	public void setEmail(String email) {
		this.email = email;
	}
	
	public void getInput() {
		Scanner input = new Scanner(System.in);
		//get user input
		System.out.println("Enter name and surname:");
		this.nameSurname=input.nextLine();
		System.out.println("Enter id:"); // Sys class'taki belki addPerson'a eklenebilir
		this.personId=input.nextInt();
		System.out.println("Enter the borrow date (dd/mm/yy):");
		input.skip("\\R");
		this.borrowDate=input.nextLine();
		System.out.println("Enter phone number:");
		this.phoneNo=input.nextLine();
		System.out.println("Enter email:");
		this.email=input.nextLine();
	}
	
	public String toString() {
		return "Person\nName Surname= "+nameSurname+"\nPerson Id= "+personId
				+"\nBorrow Date= "+borrowDate+"\nPhone Number= "+phoneNo+"\nEmail= "+email+"\n";
	}
	
}
