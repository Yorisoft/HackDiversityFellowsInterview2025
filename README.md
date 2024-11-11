
# Hack Diversity Fellow Technical Interview: Accessible Route Search and Sorting Challenge

### Overview
This technical challenge assesses your understanding of beginner-level data structures and algorithms with a real-world application focused on accessibility. You’ll create an algorithm that filters and sorts accessible routes and submit your solution through a RESTful API and GitHub.

---

### Objectives
This exercise evaluates the following key skills:
- **Data Structures**: Use arrays or linked lists.
- **Algorithms**: Implement linear search and a sorting algorithm (e.g., bubble sort, selection sort, or insertion sort).
- **API Interaction**: Retrieve and submit data via a RESTful API.
- **Version Control**: Use GitHub to submit your code with frequent commits.

---

### Language and Requirements

- **Preferred Language**: Complete the challenge in any language you’re comfortable with, as long as it enables you to:
  - Implement linear search and basic sorting algorithms.
  - Interact with RESTful APIs using `GET` and `POST` requests.
  - Use version control with Git and push code to GitHub.

- **Requirements**: Ensure your solution meets the following criteria:
  - Filters accessible routes using linear search.
  - Sorts routes by distance in ascending order using a basic sorting algorithm (bubble sort, selection sort, or insertion sort).
  - Submits a sorted list of routes to the API as specified.

---

### Preparation and Setup

1. **Fork the Repository**
   - Fork the provided repository and clone it locally. If no starter repository is provided, create a new repo for your work.
   - Make frequent commits with meaningful messages and push changes to GitHub to maintain a clear history of your progress.

2. **Time Allocation**
   - This challenge should take 30–45 minutes, including implementation, testing, and GitHub submission.

---

## Starting a New Session

To begin the interview, create a unique session. Follow these steps to initialize your session and retrieve a `session_id`, which you will use for authorization in subsequent API requests.

### Endpoint: `/api/start-session`
- **Method**: `POST`
- **Description**: Initializes a new session and returns a unique `session_id` required for authentication in subsequent requests.

### Request Body (JSON)
```json
{
    "firstName": "YourFirstName",
    "lastName": "YourLastName"
}
```

| Field     | Type   | Description          |
| --------- | ------ | -------------------- |
| firstName | string | Your first name      |
| lastName  | string | Your last name       |

### Response
If the session is created successfully, the response will include a unique `session_id` for use as a Bearer token in the Authorization header for other endpoints.

```json
{
    "session_id": "your-unique-session-id"
}
```

### Example in Postman
1. Select the `POST` method.
2. Enter the URL: `https://hackdiversity.xyz/api/start-session`
3. Add the following JSON to the request body:

    ```json
    {
        "firstName": "Jean-Jacques",
        "lastName": "Dessalines"
    }
    ```

4. Send the request.
5. Copy the `session_id` from the response and use it as your Bearer token in the Authorization header for all subsequent API requests.

### Authorization Header Format
Once you have your `session_id`, include it in the Authorization header for all API requests that require authentication.

```plaintext
Authorization: Bearer <session_id>
```

Replace `<session_id>` with the unique session ID received from the `/api/start-session` endpoint.

---

## The Task

### 1. Retrieve Route Data
- **URL**: `https://hackdiversity.xyz/api/navigation/routes`
- **Method**: `GET`
- **Authorization**: Include the `session_id` as a Bearer token in the Authorization header.

### 2. Algorithm Requirements
- **Filter**: Include only accessible routes from the data.
- **Sort**: Arrange the filtered routes by distance in ascending order using one of the following:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort

### 3. Test and Validate
- Retrieve sample data from `https://hackdiversity.xyz/api/test/mockRoutes` to test your algorithm.
- Submit test data to `https://hackdiversity.xyz/api/test/submit-sorted-routes` to validate your logic (up to 3 attempts available, which do not impact your final submission count).

### 4. Submit Final Routes
- **Final Submission URL**: `https://hackdiversity.xyz/api/navigation/sorted_routes`
- **Attempts**: Up to 10 attempts are allowed, each of which is logged for review.

### 5. Completion Status
- **Check Progress**: 
  - **URL**: `https://hackdiversity.xyz/api/navigation/status`
  - **Method**: `GET`
  - This will display your progress, remaining attempts, and feedback on prior submissions.

---

### Helpful Tips

**Algorithm Hints**  
- **Linear Search**: Traverse the list and filter items based on accessibility status.
- **Sorting**: Use a sorting algorithm (e.g., bubble sort, selection sort, or insertion sort) to order routes by distance.

**Validate Locally Before Using the Test API**  
- Build simple test cases locally to check your filtering and sorting logic before using the test API. Testing locally helps catch issues early, reducing the need for multiple API attempts.

**Read Hints in API Responses for Common Mistakes**  
- Review API responses after submissions for hints on common issues, like routes not sorted correctly or inaccessible routes included in results.

**Focus on Algorithmic Thinking**  
- This exercise assesses your understanding of data structures, filtering, and sorting. Plan and verify your algorithm before submitting.

**Using Postman**  
- **Authorization**: Add a `Bearer <session_id>` token to the Authorization header for all requests.
- **Organize Requests**: Use a Postman collection to organize requests for session setup, retrieving routes, testing, and final submission.

**Version Control and Submission**  
- **Commit Regularly**: Commit your code after completing significant tasks, such as implementing filtering or sorting.
- **Final Submission**: Push all changes to GitHub, with clear commit messages. Ensure your final code is readable and organized.

---

### Evaluation Criteria

Your submission will be evaluated on the following:

1. **Correctness**
   - Accurately filters accessible routes using linear search.
   - Correctly sorts routes in ascending order by distance.

2. **Code Quality**
   - Code should be organized and easy to read.
   - Proper use of arrays or linked lists for handling route data.

3. **Completion and Submission**
   - The correct sorted list is submitted via the API.
   - Your code is pushed to GitHub with a clear, consistent commit history.

4. **Use of GitHub**
   - Demonstrate proficiency with Git by committing regularly and following a structured workflow.

5. **Efficiency (Bonus)**
   - Minor inefficiencies are acceptable, but a well-optimized solution will score higher.

---


This challenge is an opportunity to showcase your problem-solving skills with data structures, algorithms, and APIs. Take your time to review the instructions, think through your approach, and reach out if you have any questions. We look forward to seeing your solution—GOOD LUCK 👾!
