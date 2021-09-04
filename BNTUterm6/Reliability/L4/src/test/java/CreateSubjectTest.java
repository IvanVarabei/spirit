// Generated by Selenium IDE,

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.interactions.Actions;

import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import org.junit.Test;
import org.junit.Before;
import org.junit.After;
import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.core.IsNot.not;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.remote.RemoteWebDriver;
import org.openqa.selenium.remote.DesiredCapabilities;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.Alert;
import org.openqa.selenium.Keys;
import java.util.*;
import java.net.MalformedURLException;
import java.net.URL;
public class CreateSubjectTest {
    private WebDriver driver;
    private Map<String, Object> vars;
    JavascriptExecutor js;

    @Before
    public void setUp() {
        System.setProperty("webdriver.chrome.driver",
                Paths.get("src/test/resources/chromedriver_win32/chromedriver.exe").toString());
        driver = new ChromeDriver();
        js = (JavascriptExecutor) driver;
        vars = new HashMap<String, Object>();
    }

    @After
    public void tearDown() {
        driver.quit();
    }

    @Test
    public void createSubject() throws InterruptedException {
        driver.get("https://educats.by/login?returnUrl=%2Fweb%2Fdashboard");
        driver.manage().window().setSize(new Dimension(1477, 880));
        driver.findElement(By.id("mat-input-0")).sendKeys("testLecturer1");
        driver.findElement(By.id("mat-input-1")).sendKeys("testLecturer1");
        driver.findElement(By.cssSelector(".loginbtn > .mat-focus-indicator")).click();
        Thread.sleep(6000);
        driver.findElement(By.cssSelector("body > app-root > div > app-content-layout > app-nav > mat-toolbar.mat-toolbar.mat-elevation-z6.main-toolbar.first.mat-primary.mat-toolbar-single-row > div:nth-child(3) > a"))
                .click();
        Thread.sleep(2000);
        driver.findElement(By.cssSelector("body > app-root > div > app-content-layout > app-subjects-nav > mat-toolbar > button")).click();
        Thread.sleep(6500);
        driver.findElement(By.cssSelector(".mat-raised-button")).click();
        {
            WebElement element = driver.findElement(By.tagName("body"));
            Actions builder = new Actions(driver);
            builder.moveToElement(element, 0, 0).perform();
        }
        driver.switchTo().frame(0);
        driver.findElement(By.cssSelector(".mat-raised-button > .mat-button-wrapper")).click();
        Thread.sleep(3000);
        driver.findElement(By.id("mat-input-0")).click();
        driver.findElement(By.id("mat-input-0")).sendKeys("CREATE");
        driver.findElement(By.id("mat-input-1")).click();
        driver.findElement(By.id("mat-input-1")).sendKeys("CRT");
        driver.findElement(By.cssSelector("#mat-dialog-0 > app-news-popover > div > div.mat-dialog-actions > button.mat-raised-button.mat-primary"))
                .click();
        Thread.sleep(3000);
        assertThat(driver.findElement(By.cssSelector(".mat-row:nth-child(11) > .cdk-column-name")).getText(), is("CREATE"));
    }
}
