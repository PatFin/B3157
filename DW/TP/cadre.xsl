<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html"/>
	<xsl:template match="/">
		<html>
			<head>
				<title>XSLT Excercises</title>
				<STYLE>
					H1 {COLOR: red; FONT-FAMILY: Arial; FONT-SIZE: 14pt;}
					H2 {COLOR: darkblue; FONT-FAMILY: Arial; FONT-SIZE: 12pt;}
					.subhead {COLOR: darkblue; FONT-FAMILY: Arial; FONT-SIZE: 12pt;}
					.text {COLOR: black; FONT-FAMILY: Arial; FONT-SIZE: 12pt;}
					TH {COLOR: white; FONT-FAMILY: Arial; background-color:
					darkblue;}
					TD {COLOR: blue; FONT-FAMILY: Arial}
					TR { background-color: beige; }
					BODY { background-color: beige; }
				</STYLE>
			</head>
			<body>
				<H1>Company Information for Infoteria</H1>
				<H2>Employee Listing</H2>
				<table border="1">
					<tr>
						<th>Name</th>
						<th>Position</th>
						<th>E-mail</th>
					</tr>
					<!-- On insère les employés ici, appel au xsl template d'employee-->
					<!--<xsl:apply-templates/> -->

					<!-- Ou alors on écris le xsl directement ici -->
					<xsl:for-each select="//Employee">
						<tr>
							<td><xsl:value-of select="LastName"/><xsl:text> </xsl:text><xsl:value-of select="FirstName"/></td>
							<td><xsl:value-of select="Position"/></td>
							<td><xsl:value-of select="Email"/></td>
						</tr>
					</xsl:for-each>

					</table>
				<p>
					Total Employees: <xsl:value-of select="count(//Employee)"/>
				</p>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="Employee">
		<tr>
			<td><xsl:value-of select="LastName"/><xsl:text> </xsl:text><xsl:value-of select="FirstName"/></td>
			<td><xsl:value-of select="Position"/></td>
			<td><xsl:value-of select="Email"/></td>
		</tr>
	</xsl:template>
</xsl:stylesheet>
