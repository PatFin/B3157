<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html" version="1.0" indent="yes"/>
	<xsl:template match="/">

		<xsl:for-each select="//event">
		<xsl:sort select="title" />
			<div class="event">
				<h4><xsl:value-of select="title" /></h4>
				<ul>
					<li>
						<xsl:text>le </xsl:text>
						<xsl:value-of select="substring(dtstart,7,2)" />
						<xsl:text>-</xsl:text>
						<xsl:value-of select="substring(dtstart,5,2)" />
						<xsl:text>-</xsl:text>
						<xsl:value-of select="substring(dtstart,1,4)" />
						<xsl:text> de </xsl:text>
						<xsl:value-of select="substring(dtstart,10,2)" />
						<xsl:text>h</xsl:text>
						<xsl:value-of select="substring(dtstart,11,2)" />
						<xsl:text> à </xsl:text>
						<xsl:value-of select="substring(dtend,10,2)" />
						<xsl:text>h</xsl:text>
						<xsl:value-of select="substring(dtend,11,2)" />
					</li>
					<li>
						<xsl:value-of select="summary" />
					</li>
					<li>
						<xsl:value-of select="url" />
					</li>
					<li>
						<xsl:value-of select="description" />
					</li>
				</ul>
			</div>
		</xsl:for-each>

	</xsl:template>
</xsl:stylesheet>
