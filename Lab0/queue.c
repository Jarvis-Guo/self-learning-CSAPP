/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    list_ele_t *cur = q->head;
    list_ele_t *next;
    while (cur != NULL) {
        next = cur->next;
        free(cur->value);
        free(cur);
        cur = next;
    }
    
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    char *value = malloc(strlen(s) + 1);
    if (value == NULL) {
        free(newh);
        return false;
    }
    memcpy(value, s, strlen(s) + 1);
    //strcpy(value, s);
    newh->value = value;
    newh->next = q->head;
    if (newh->next == NULL) {
        q->tail = newh;
    }
    q->head = newh;
    (q->size)++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newElement = malloc(sizeof(list_ele_t));
    if (newElement == NULL) {
        return false;
    }
    char *value = malloc(strlen(s) + 1);
    if (value == NULL) {
        free(newElement);
        return false;
    }
    // 以下两种方式都是可行的
    memcpy(value, s, strlen(s) + 1);
    //strcpy(value, s);
    newElement->value = value;
    newElement->next = NULL;
    if (q->head == NULL) {
        q->head = newElement;
    } else {
        q->tail->next = newElement;
    }
    q->tail = newElement;
    (q->size)++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL) {
        return false;
    }
    list_ele_t *cur = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    (q->size)--;
    if (buf != NULL) {
        strncpy(buf, cur->value, bufsize - 1);
        buf[bufsize - 1] = '\0';
    }
    free(cur->value);
    free(cur);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL) {
        return 0;
    }
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (queue_size(q) != 0) {
        list_ele_t *newNext = NULL;
        list_ele_t *cur = q->head;
        list_ele_t *newHead;
        q->tail = cur;
        do {
            newHead = cur->next;
            cur->next = newNext;
            newNext = cur;
            cur = newHead;
        } while (cur != NULL);
        q->head = newNext;
    }
}
