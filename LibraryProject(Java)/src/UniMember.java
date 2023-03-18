
public class UniMember extends Person{


	
	public UniMember() {
		super();
		numOfPeople++;
	}
	
	public UniMember(String nameSurname,int personId,String borrowDate,String phoneNo,String email)
	{
		super(nameSurname,personId,borrowDate,phoneNo,email);
	}

	
	public void getInput() {
		
		super.getInput();
	}
	
	public String toString() {
		
		return super.toString();
	}
	
	
	}