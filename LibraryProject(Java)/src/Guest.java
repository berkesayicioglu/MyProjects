import java.util.Scanner;

public class Guest extends Person {
	
	private double fee;
	
	public Guest() {
		
		super();
		numOfPeople++;
		
	}

	public Guest(String nameSurname,int personId,String borrowDate,String phoneNo,String email) {
		
		
		super(nameSurname,personId,borrowDate,phoneNo,email);
		
	}

	public double getFee() {
		return fee;
	}

	public void setFee(double fee) {
		this.fee = fee;
	}

	public void getInput() {
		Scanner sc = new Scanner(System.in);
		super.getInput();
		System.out.println("Enter fee:");
		fee=sc.nextDouble();
		
	}
	@Override
	public String toString() {
		return "Guest\n" + super.toString()
			+ "\nFee = " + fee;
	}
	
	public double calculateFee() {
		
		//burası updatelenecek
		return fee;
	}
	
}
