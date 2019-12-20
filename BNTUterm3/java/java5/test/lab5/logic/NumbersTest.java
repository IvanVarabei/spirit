package lab5.logic;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import lab5.model.Numbers;

public class NumbersTest {

	private Numbers instance = null;
	
	@Before
	public void init0() {
		System.out.println("Before1 test");
		instance = new Numbers();
	}

	@Before
	public void init1() {
		System.out.println("Before2 test");
		instance = new Numbers();
	}

	@After
	public void destroy0() {
		System.out.println("After1 test");
		instance = null;
	}
	
	@After
	public void destroy1() {
		System.out.println("After2 test");
		instance = null;
	}

	@Test
	public void testApproxArifm() {

		double expected = instance.approxArifm(7391);
		if (expected != 5) {
			fail();
		}
		expected = instance.approxArifm(1);
		if (expected != 1) {
			fail();
		}
		expected = instance.approxArifm(1000);
		if (expected != 0.25) {
			fail();
		}
	}

	@Test
	public void testApproxGeom() {
		double expected = instance.approxGeom(7391);
		if (Math.round(expected*100.0)/100.0 != 3.71) {
			fail();
		}
		expected = instance.approxGeom(1);
		if (Math.round(expected*100.0)/100.0 != 1.0) {
			fail();
		}
		expected = instance.approxGeom(1000);
		if (Math.round(expected*100.0)/100.0 != 0.0) {
			fail();
		}
		
	}

}
