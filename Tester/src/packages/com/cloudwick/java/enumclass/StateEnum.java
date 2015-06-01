package packages.com.cloudwick.java.enumclass;

public enum StateEnum {
	
	   CA("1",94646),
	   TX("2",84567),
	   UT("7",76453);
	   private StateEnum(String id, int zip){
		
		   this.StateID = id;
		   this.postalcode = zip;
	   }
	   private String StateID;
	   private int postalcode;
	/**
	 * @return the stateID
	 */
	public String getStateID() {
		return StateID;
	}
	
	/**
	 * @param stateID the stateID to set
	 
	public void setStateID(String stateID) {
		StateID = stateID;
	}
	/**
	 * @return the postalcode
	 */
	public int getPostalcode() {
		return postalcode;
	}
	
	/**
	 * @param postalcode the postalcode to set
	 
	public void setPostalcode(int postalcode) {
		this.postalcode = postalcode;
	}
	   
	*/
}
