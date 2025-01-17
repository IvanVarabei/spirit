package patterns.behavioral.mediator;

public class MainTest {

	public static void main(String ...dg) throws InterruptedException {
		AtcMediatorImpl atcMediator = new AtcMediatorImpl();
		atcMediator.registerRunway(new Runway("RW-1",false));
		atcMediator.registerGate(new Gate("G-1",false));
		atcMediator.registerGate(new Gate("G-2",false));
		atcMediator.registerGate(new Gate("G-3",false));
		
		for(int i = 0; i<10; i++) {
			Flight flight = new Flight(atcMediator, "F-00"+(i+1));
			flight.landAndTakeOff();
		}
	}

}
