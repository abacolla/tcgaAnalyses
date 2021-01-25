args=(commandArgs(TRUE))

var1 <- args[1]
var1

options(echo=FALSE)
setwd(args[2])

filename <- paste("all",var1,".txt",sep="")
myData <- read.table(file = filename, sep="\t", header=FALSE)
colnames(myData) <- c("Gene_Expr", "Tumor_Type", "Group")
myData$`Tumor_Type` <- as.character(myData$`Tumor_Type`)
myData$`Tumor_Type` <- factor(myData$`Tumor_Type`, levels=unique(myData$`Tumor_Type`))
head(myData)
xlabs <- paste(levels(myData$`Tumor_Type`), "\n(n=", table(myData$`Tumor_Type`),")", sep="")

library(ggplot2)
library(ggpubr)
library(grid)
library("extrafont")

# compare_means using ggpubr
compare_means(formula = Gene_Expr ~ Group, 
              data = myData, 
			  group.by = "Tumor_Type", 
			  method = "wilcox.test",
			  p.adjust.method = "holm")

ppi <- 300

boxName <- paste("boxPlotGeneExpr",var1,".png", sep="")
title <- paste(var1,"expression", sep=" ")

png(file = boxName, width = 5, height = 3, units = 'in', res = ppi)                    
plot <- ggplot(myData, aes(x = `Tumor_Type`, 
                           y = Gene_Expr, 
						   fill = Group)) +
     stat_boxplot(geom = "errorbar",
	              width = 0.40,
				  position = position_dodge(0.68),
				  size = 0.2) +
     geom_boxplot(width = 0.47, 
	              position = position_dodge(0.68),
				  size = 0.2, 
				  outlier.size = 0.2,
				  notch = FALSE) +
     theme_classic(base_line_size = 0.2) +
     ggtitle(title) +
     ylab("log2(normalized rsem + 1)") +
     scale_x_discrete(labels = xlabs) +
     rotate_x_text(angle = 90) +
	 ylim(3,14) +
	 stat_compare_means(aes(group = Group), label = "p.format", label.y = 14.0, size = 1.2, color = "red", angle = 45) +
     theme(
           plot.title = element_text(family = "Times New Roman", face = "bold.italic", color = "darkred", size = 8, hjust = 0.5),
           axis.title.x = element_text(family = "Helvetica", face = "plain", color = "black", size = 6),
           axis.title.y = element_text(family = "Helvetica", face = "plain", color = "black", size = 6),
           legend.text = element_text(family = "Helvetica", face = "plain", color = "black", size = 6),
           legend.title = element_text(family = "Helvetica", face = "italic", color = "black", size = 6),
		   axis.ticks.length = unit(-0.1, "cm"),
		   axis.text.x = element_text(margin=unit(c(0.2,0.2,0.2,0.2), "cm"),
		                              family = "Helvetica",
									  face = "plain",
									  color = "black",
									  size = 6),
		   axis.text.y = element_text(margin=unit(c(0.2,0.2,0.2,0.2), "cm"),
		                              family = "Helvetica", 
									  face = "plain", 
									  color = "black", 
									  size = 6),
		   axis.line.x = element_line(size = 2, colour = "white"),
           legend.position = "right") +
	  scale_fill_manual(values=c("#6495ED", "#FF6347"))

plot

dev.off()

#     stat_boxplot(geom = "errorbar", width = 0.47, size = 0.2) +
#     geom_dotplot(binaxis = 'y', stackdir = 'center', dotsize = 0.1) +
#      geom_violin(position = position_dodge(0.68),
#                 size = 0.2) +

#     guides(color = guide_legend(override.aes = list(size = 2, alpha = 1)))
#     stat_summary(fun.y = mean, geom = "point", shape = 23, size = 2, col = "black", fill = "black") + 
