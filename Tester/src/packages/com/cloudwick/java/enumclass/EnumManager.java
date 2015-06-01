package packages.com.cloudwick.java.enumclass;

public class EnumManager {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
//		System.out.println(StateEnum.CA.getStateID());
	//	System.out.println(StateEnum.TX.getPostalcode());
		for(StateEnum e : StateEnum.values()){
		System.out.println(e.getStateID());
		System.out.println(e.getPostalcode());
			
		}

	}

}
