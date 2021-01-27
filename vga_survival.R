args=(commandArgs(TRUE))

library(dplyr)
library(survival)
library(survminer)
setwd(args[5])

table <- paste(args[1], args[4], "survival", sep="_")
label1 <- paste(args[4], "Low", sep="_")
label2 <- paste(args[4], "High", sep="_")
heading1 <- paste("Kaplan-Meier curve", args[3], "in", args[2], sep=" ")
heading2 <- paste(args[1], "_", args[4], ".png", sep="")

data <- read.table(file = table, sep = "\t", header = TRUE, dec = ".", numerals = "no.loss")
getX <- as_tibble(data)
val <- mean(getX$geneExp)
getX <- getX %>% mutate(geneLev=cut(geneExp, breaks=c(0, val, Inf), labels=c(label1, label2)))
survp <- ggsurvplot(survfit(Surv(time, status)~geneLev, data=getX), 
			pval=TRUE,
#			risk.table = TRUE, 
#			risk.table.height=0.15,
			title = heading1,
			palette = c("#3333FF", "#FF3300"),
			size = 1.5)

#ggsave(file = "exo5_acc.png", width = 4.0, height = 4.0, dpi = 100)
png(heading2)
print(survp)
dev.off()

fitCox <- coxph(Surv(time, status)~geneLev, data=getX)
fitCox
summary(fitCox)
