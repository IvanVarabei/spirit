package by.bntu.fitr.nameofstudent.javalabs.lab07.model;

import static org.junit.Assert.*;

import org.junit.Test;

import by.bntu.fitr.varabei.javalabs.lab07.model.Mood;

public class MoodTest {

	@Test
	public void testDetermineSpirits() {
		boolean first = false, second = false, therd = false;
		for (int i = 0; i < 100; i++) {
			if (Mood.determineSpirits() == "=)") {//const
				first = true;
			}
			if (Mood.determineSpirits() == "=|") {
				second = true;
			}
			if (Mood.determineSpirits() == "=(") {
				therd = true;
			}
		}
		if (first==false || second==false || therd==false) {
			fail();
		}
	}

}
