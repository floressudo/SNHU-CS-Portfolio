# CS-305: Software Security
Project Practices for Secure Software - Artemis Financial

## Project Summary

For this project, I conducted a vulnerability assessment and completed security refactoring for Artemis Financial, a financial consulting company. The course required auditing an existing RESTful web application using OWASP Dependency-Check, establishing secure communications by configuring TLS and HTTPS on port 8443 with a PKCS12 keystore, and implementing data integrity verification using Java's MessageDigest with SHA-256 to create a secure checksum endpoint.

## Reflection

### Client Summary and Software Requirements
Artemis Financial is a financial consulting firm that provides investment, banking, and financial advice to clients. Because they handle sensitive personal and financial data, including international investments and retirement funds, they needed their software to be secure and reliable. The company wanted me to address security vulnerabilities in their web application. Specifically, their existing system was sending data over unencrypted HTTP on port 8080, lacked a way to verify that transaction data had not been modified during transit, and relied on third-party dependencies that needed to be audited for known vulnerabilities.

### Identifying Vulnerabilities and the Value of Secure Coding
When assessing the client's software, I did well at following the vulnerability assessment process flow diagram step by step to identify where the application was exposed. I reviewed the codebase, inspected how data moved across the network, and identified missing security controls. Secure coding is important because a single weakness can expose sensitive financial records and bank details to anyone monitoring traffic. For Artemis Financial, software security is not just a technical checklist; it protects client trust and the firm's reputation. It also prevents legal issues and costly regulatory fines under frameworks like GDPR and financial privacy regulations. Protecting the system from data leaks and tampering keeps the business stable and gives clients confidence that their money and records are safe.

### Challenging and Helpful Aspects of the Vulnerability Assessment
The most helpful part of the assessment was using OWASP Dependency-Check within the Maven build cycle. Being able to scan project libraries automatically and see a report of known CVEs helped me understand where external risks come from. The most challenging part was configuring the PKCS12 keystore and setting up TLS certificates correctly in Spring Boot. I had to generate the self-signed certificate, export the .cer file, place the keystore in the project resources, and configure application.properties to use HTTPS on port 8443 without breaking the build. Working through those errors helped me see how certificates, keystores, and secure ports connect in practice.

### Increasing Layers of Security and Future Mitigation Strategies
Instead of depending on just one fix, I implemented multiple layers of defense:
- Transport Layer: I replaced open HTTP on port 8080 with HTTPS on port 8443, using TLS encryption so network traffic cannot be intercepted in plain text.
- Application Layer: I refactored the controller to use Java's MessageDigest with SHA-256 to provide data integrity verification through a /hash endpoint. This produces a fixed 256-bit digest so clients can verify data was not modified during transfer.
- Build and Dependency Layer: I used OWASP Dependency-Check to scan Maven dependencies for known vulnerabilities before deployment.

In the future, I would assess vulnerabilities by combining automated scanners like OWASP with manual code reviews against industry standards like the OWASP Top 10 and NIST guidelines. To decide on mitigation techniques, I would evaluate the risk level, the sensitivity of the data handled, and whether the fix provides defense in depth without adding unnecessary complexity.

### Ensuring Functionality and Verifying Refactored Code
I made sure the software was functional by running the Spring Boot application and testing the endpoints directly. I accessed the /hash endpoint over HTTPS in the browser and confirmed that it returned the expected output with the SHA-256 digest. I also verified that the application rejected insecure HTTP connections on port 8080. After refactoring the code to add the checksum logic and certificate configuration, I re-ran the OWASP Dependency-Check scan to confirm that no new dependency vulnerabilities were added during the refactoring process. This secondary testing step gave me confidence that the application remained functional while becoming significantly more secure.

### Tools, Resources, and Coding Practices for Future Projects
Several tools and practices from this project will help me in future software projects:
- Java Security API: Using standard libraries like java.security.MessageDigest instead of writing custom cryptographic methods.
- OWASP Dependency-Check: Running static vulnerability scans regularly during the build process to catch insecure dependencies early.
- Keystore Management: Using the keytool utility to manage certificates and PKCS12 keystores for secure communications.
- Secure Defaults: Always configuring applications to use encrypted protocols by default and separating configuration properties cleanly.
- The Vulnerability Assessment Flowchart: Approaching security systematically by analyzing client needs, identifying exposure points, applying targeted mitigations, and testing before deployment.

### What to Showcase to Future Employers
From this project, I can show employers my completed Practices for Secure Software Report and the refactored Spring Boot codebase. These artifacts demonstrate that I can take existing code with known vulnerabilities, systematically identify the risks, and implement practical solutions. It shows that I understand how to configure HTTPS and TLS certificates, how to use SHA-256 cryptographic hashes to verify data integrity, and how to use automated tools like OWASP Dependency-Check to maintain secure builds. It proves that I take security seriously and think about protecting data at both the network and application levels.
