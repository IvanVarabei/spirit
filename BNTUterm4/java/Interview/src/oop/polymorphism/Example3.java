package oop.polymorphism;

class Print1{
	private void print() {
		System.out.println("777");
	}
	void print(Print1 p) {
		p.print();
	}
}

class Print2 extends Print1{
	void print() {
		System.out.println("666");
	}
}


public class Example3 {

	public static void main(String ...ew) {
		Print1 p = new Print1();
		Print2 q = new Print2();
		p.print(q);
	}
}
