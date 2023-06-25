#Kyle White
#KGW190000 CS 4375.002 A1

#When loading the packages, remove the comment signs.
#install.packages('ggplot2')
#install.packages('sampling')
#install.packages('scatterplot3d')
#install.packages('arules')
#install.packages('Matrix')

library(ggplot2)
library(sampling)
library(scatterplot3d)
library(arules)
library(Matrix)
library(dplyr)
library("knitr")

#creating data frame from the heart.csv file.
heartfailuredataset <- read.table("heart.csv", sep=",", header= TRUE)

#Increase the amount of rows that are scanned from the data set.
options(max.print=1000000)

#1c
#Checking for missing values, and ensuring there are none.
is.na(heartfailuredataset)
which(is.na(heartfailuredataset))
sum(is.na(heartfailuredataset))

#Checking for duplicate objects, and ensuring there are none.
i <- duplicated(heartfailuredataset)
i
which(i)

#Assigning cleaend data frame, and double checking for no duplicated values.
clean.heartfailuredataset <- unique(heartfailuredataset[complete.cases(heartfailuredataset),])
summary(clean.heartfailuredataset)
duplicated(clean.heartfailuredataset)


#1d
#Histogram of Age.
#Fixing "x must be numeric error"
age <- as.numeric(clean.heartfailuredataset$Age)
hist(age)

#Boxplot of RestingBP.
boxplot(clean.heartfailuredataset$RestingBP, horizontal = TRUE)

#Plot of Cholesterol levels.
plot(clean.heartfailuredataset$Cholesterol)

#Barpot of Maximum Heartrate.
barplot(clean.heartfailuredataset$MaxHR)

#Histogram of Oldpeak #'s.
hist(clean.heartfailuredataset$Oldpeak)

#1e
#Showcasing boxplots of relations between continuous and discrete variables.
#Setting discrete variables to act as a numeric value relator.
clean.heartfailuredataset$Age <- as.factor(clean.heartfailuredataset$Age)
clean.heartfailuredataset$Sex <- as.factor(clean.heartfailuredataset$Sex)
#Age in this case would be considered the discrete variable, since it has no decimal.
a <- boxplot(RestingBP ~ Age, data = clean.heartfailuredataset, horizontal = TRUE)
a
b <- boxplot(RestingBP ~ Sex, data = clean.heartfailuredataset, horizontal = TRUE)
b
c <- boxplot(Cholesterol ~ Age, data = clean.heartfailuredataset, horizontal = TRUE)
c
d <- boxplot(Cholesterol ~ Sex, data = clean.heartfailuredataset, horizontal = TRUE)
d
e <- boxplot(MaxHR ~ Sex, data = clean.heartfailuredataset, horizontal = TRUE)
e

#2
#Aggregate according to Sex.
#Extracting continuous variables to a value for reading. In this case, we will include Age as continuous.
contvariables <- select(clean.heartfailuredataset, Age, RestingBP, Cholesterol, FastingBS, MaxHR, Oldpeak)
aggregate(.~clean.heartfailuredataset$Sex, data=contvariables, FUN = function(x) mean(as.numeric(as.character(x))))


#3
#Standardize to scale.
contvariables.scaled <- scale(contvariables[1:4])
summary(contvariables.scaled)
#Compare 10 objects, both before and after scaling.
#Before
dist(contvariables[1:10,], method="euclidean") 
#After
dist(contvariables.scaled[1:10,], method="euclidean")


#4
#Creating random sample of 300 objects of the improved data set.
samples <- sample(1:nrow(clean.heartfailuredataset), 300)
samples
randomsample <- clean.heartfailuredataset[samples,]

#Checking for duplicated objects in the sample.
i <- duplicated(randomsample)
i

#5
#Extracting RestingBP, Cholesterol, and FastingBS from the data set.
extracted <- select(clean.heartfailuredataset, RestingBP, Cholesterol, FastingBS)
extracted
#Drawing scatterplot3d of the extracted data; Age in this case would be considered a discrete variable.
#Sex, without altering the variable, doesn't work on this scatterplot.
scatterplot3d(extracted, color=as.integer(clean.heartfailuredataset$Age))

#Ensuring they can be charted for data.
clean.heartfailuredataset$RestingBP <- as.numeric(clean.heartfailuredataset$RestingBP)
clean.heartfailuredataset$Cholesterol <- as.numeric(clean.heartfailuredataset$Cholesterol)
clean.heartfailuredataset$FastingBS <- as.numeric(clean.heartfailuredataset$FastingBS)

#PCA Method
pc <- prcomp(as.matrix(extracted))
pc

#Importance of each component.
plot(pc)

#Plot the data points into a 2D area using PCA method.
plot(pc$x, col=clean.heartfailuredataset$Age)


#6
#Discretize age into 4 different categories.
#Remember to load the data frame again to revert back to original default values after scaling.
#Equal Interval
dAge <-discretize(heartfailuredataset$Age, method="interval", breaks=4)
summary(dAge)
#Equal Frequency
dAge <-discretize(heartfailuredataset$Age, method="frequency", breaks=4)
summary(dAge)


#7
#Extract two continuous features.
twocont <- select(clean.heartfailuredataset, RestingBP, Cholesterol)
#Extract 50 objects.
twocontsample <- twocont[1:50,]
#Display modified data.
twocontsample
#Pearson correlation matrix
cor(twocontsample)




#Kyle White
#KGW190000 CS 4375.002 A4



#2
library(cluster)

data <- data.frame(
  Tid = 1:10,
  HomeOwner = c("Yes", "No", "No", "Yes", "No", "No", "Yes", "No", "No", "No"),
  MaritalStatus = c("Single", "Married", "Single", "Married", "Divorced", "Married", "Divorced", "Single", "Married", "Single"),
  TaxableIncome = c(125000, 100000, 70000, 120000, 95000, 60000, 220000, 85000, 75000, 90000),
  DefaultedBorrower = c("No", "No", "No", "No", "Yes", "No", "No", "Yes", "No", "Yes")
)

# convert the nominal HomeOwner and MaritalStatus columns to factors
data$HomeOwner <- as.factor(data$HomeOwner)
data$MaritalStatus <- as.factor(data$MaritalStatus)


# select the HomeOwner and MaritalStatus columns
data_subset <- data[, c("HomeOwner", "MaritalStatus")]

# calculate the dissimilarity matrix using the Manhattan distance
dissimilarity_matrix <- daisy(data_subset, metric = "manhattan")

# view the dissimilarity matrix
dissimilarity_matrix



#4
# Create a sample dataset with 3 attributes and 10 objects
data <- data.frame(
  Person_ID = c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
  Home_Owner = c("Yes", "No", "Yes", "No", "Yes", "No", "No", "No", "No", "Yes"),
  Refund = c("TRUE", "TRUE", "FALSE", "FALSE", "FALSE", "FALSE", "TRUE", "TRUE", "TRUE", "TRUE")
)

# Set the number of bootstrap samples to generate
num_samples <- 10

# Generate the bootstrap samples
bootstrap_samples <- lapply(1:num_samples, function(i) sample(unique(data$Person_ID), replace=TRUE))
bootstrap_samples

# Extract the data for each bootstrap sample
bootstrap_data <- lapply(bootstrap_samples, function(indices) data[data$Person_ID %in% indices,])
bootstrap_data

#Create a decision tree using the training set.
for(i in 1:length(bootstrap_data)) {
stump <- rpart(Home_Owner ~., data=data[-folds[[i]],],control=rpart.control(minsplit=0))
}
stump

#5
# Create the data frame
data <- data.frame(
  A = c(1.0, 3.0, 4.5, 3.5, 2.5, 3.0, 2.0),
  B = c(1.0, 2.0, 6.0, 4.0, 4.0, 3.0, 2.0)
)

# Specify the number of clusters and the initial centers
k <- 2
centers <- data[c(1, 4), ]

# Run the K-means algorithm with the specified initial centers
km <- kmeans(data, centers = centers, nstart = 1)

# Print the results
print(km)
plot(data, col = km$cluster, pch = 19, main = "K-means Clustering")
points(km$centers, col = 1:k, pch = 8, cex = 2)


#6-9***
#install.packages('mlbench')
#install.packages('rpart')
#install.packages('rpart.plot')
#install.packages('caret')
#install.packages('lattice')
#install.packages('e1071')
#install.packages('doParallel')
#install.packages('foreach')
#install.packages('iterators')
#install.packages('parallel')
#install.packages('aggTrees')
#install.packages('pROC')

library(mlbench)
library(rpart)
library(rpart.plot)
library(ggplot2)
library(lattice)
library(e1071)
library(caret)
library(parallel)
library(iterators)
library(foreach)
library(doParallel)
library(aggTrees)
library(caret)

library(sampling)
library(scatterplot3d)
library(arules)
library(Matrix)
library(dplyr)

#creating data frame from the heart.csv file.
heartfailuredataset <- read.table("heart.csv", sep=",", header= TRUE)

#Increase the amount of rows that are scanned from the data set.
options(max.print=1000000)

#Checking for missing values, and ensuring there are none.
is.na(heartfailuredataset)
which(is.na(heartfailuredataset))
sum(is.na(heartfailuredataset))

#Checking for duplicate objects, and ensuring there are none.
i <- duplicated(heartfailuredataset)
i
which(i)

#Assigning cleaned data frame, and double checking for no duplicated values.
clean.heartfailuredataset <- unique(heartfailuredataset[complete.cases(heartfailuredataset),])
summary(clean.heartfailuredataset)
duplicated(clean.heartfailuredataset)


#6
#Create a tree based on the training set, and repeat the process for every other fold.
#i - 1 represents cutting off the first partition fold as that is considered the testing set.
accs <- vector(mode="numeric")
for(i in 1:length(folds)) {
  tree <- rpart(HeartDisease ~., data=clean.heartfailuredataset[-folds[[i]],], control=rpart.control(minsplit=2))
  accs[i] <- accuracy(clean.heartfailuredataset[folds[[i]],]$HeartDisease, predict(tree, clean.heartfailuredataset[folds[[i]],], HeartDisease="class"))
}
accs

#Get the testing data set.
testingds <- clean.heartfailuredataset[folds[[1]],]

#Find the average accuracy.
avgacc <- mean(accs)
avgacc

#Find the average testing error.
1-mean(avgacc)

library(caret)
fit <- train(HeartDisease ~ ., data = clean.heartfailuredataset , method = "rpart",
             control=rpart.control(minsplit=2),
             trControl = trainControl(method = "cv", number = 10),
             tuneLength=5)
fit

fit$bestTune

#7
#A model using the best tuning parameters and using all the data is available as fit$finalModel.
fit$finalModel

rpart.plot(fit$finalModel, extra = 1, under = TRUE,  varlen=0, faclen=0)

#Here is the variable importance without competing splits
varImp(fit, compete = FALSE)
dotPlot(varImp(fit, compete=FALSE))

#8
impt_variables<- select(clean.heartfailuredataset, ST_Slope, Cholesterol, ExerciseAngina, MaxHR, Sex, HeartDisease)

impt_variables.scaled <- scale(impt_variables[1:4])
summary(impt_variables.scaled)

